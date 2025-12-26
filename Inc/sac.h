/* SPDX-License-Identifier: MIT */
/*!
 * \file sac.h
 * \brief Statistical Accumulator (SAC) for computing statistics on-the-fly.
 * \details This header file defines a statistical accumulator structure and
 * associated functions for computing basic statistics such as count, average,
 * standard deviation, minimum, and maximum in an online manner.
 */

#ifndef SAC_H
#define SAC_H

#include <limits.h>
#include <math.h>

/*!
 * \brief Scalar type used for statistical calculations.
 * \details Defines the scalar type used for statistical calculations in the SAC module.
 * This can be overridden to use a different floating-point type.
 */
#ifndef SAC_SCALAR_T
#define SAC_SCALAR_T float
#endif

typedef SAC_SCALAR_T sac_scalar_t;

/*!
 * \brief Size type used for counting elements in the statistical accumulator.
 * \details Defines the size type used for counting elements in the SAC module.
 * This can be overridden to use a different size type.
 */
#ifndef SAC_SIZE_T
#define SAC_SIZE_T size_t
#endif

typedef SAC_SIZE_T sac_size_t;

/*!
 * \brief Quiet Not a Number (NaN) constant.
 * \details Defines a quiet NaN constant for the SAC module. This constant is
 * used to indicate invalid or undefined results in statistical computations.
 */
#ifndef SAC_NAN
#define SAC_NAN NAN
#endif

/*!
 * \brief Square root function.
 * \details Defines the square root function used by the SAC module. This can be
 * overridden to use a custom square root implementation.
 */
#ifndef SAC_SQRT
#define SAC_SQRT sqrtf
#endif

/*!
 * \brief Statistical accumulator structure.
 * \details This structure holds the necessary data to compute statistics
 * incrementally.
 *
 * Members:
 *
 * - n: Count of values added.
 * - sigmaX: Sum of the values.
 * - sigmaX2: Sum of the squares of the values.
 * - min: Minimum value encountered.
 * - max: Maximum value encountered.
 *
 * Structures of the `statistical_accumulator` type emulate a scientific
 * calculator in statistical mode. You can use it to compute the following
 * statistics:
 *
 * - arithmetic mean (average)
 * - standard deviation, sample-based
 * - standard deviation, population-based
 * - minimum
 * - maximum
 *
 * Use the `sac_add` function as an operator to add data to the accumulator.
 * This is equivalent to the M+ button on a calculator. The statistics are
 * updated to reflect the new data value.
 *
 * All the accumulator's behaviors involve floating-point operations if your
 * `SAC_SCALAR_TYPE` type is `float` or `double`. So, these structures should
 * not normally be used in interrupt handlers unless the floating-point unit
 * permits re-entrancy. The statistics are only partially computed when the data
 * are added to the accumulator. The mean and standard deviation statistics are
 * calculated from the sum of the data and the sum of the data squared only when
 * the caller invokes the member functions. The `sac_avg`, `sac_st_dev` and
 * `sac_st_dev_p` operations are therefore relatively slow. The `sac_count`,
 * `sac_min`, and `sac_max` operations are fast.
 *
 * The API provides the following interface:
 *
 *         sac_add(SAC_SCALAR_TYPE x)
 *         sac_sub(SAC_SCALAR_TYPE x)
 *         void sac_clear()
 *         unsigned int sac_count() const
 *         SAC_SCALAR_TYPE sac_avg() const
 *         SAC_SCALAR_TYPE sac_st_dev() const
 *         SAC_SCALAR_TYPE sac_st_dev_p() const
 *         SAC_SCALAR_TYPE sac_var() const
 *         SAC_SCALAR_TYPE sac_min() const
 *         SAC_SCALAR_TYPE sac_max() const
 *
 * The first three modify the state of an accumulator. The other member functions
 * access the statistical information.
 *
 * Accumulator objects do not throw exceptions. The quiet SAC_NaN
 * constant is returned to indicate an error.
 */
struct statistical_accumulator {
    /*!
     * \brief Count of values added to the accumulator.
     * \details This member keeps track of the number of values that have been
     * added to the accumulator.
     */
    sac_size_t n; /* n */
    /*!
     * \brief Sum of values added to the accumulator.
     * \details This member holds the cumulative sum of all values added to
     * the accumulator.
     */
    sac_scalar_t sigmaX; /* sum of x */
    /*!
     * \brief Sum of squares of values added to the accumulator.
     * \details This member holds the cumulative sum of the squares of all values added to
     * the accumulator.
     */
    sac_scalar_t sigmaX2; /* sum of x * x */
    /*!
     * \brief Minimum value encountered.
     * \details This member holds the minimum value that has been added to
     * the accumulator.
     */
    sac_scalar_t min; /* minimum of x */
    /*!
     * \brief Maximum value encountered.
     * \details This member holds the maximum value that has been added to
     * the accumulator.
     */
    sac_scalar_t max; /* maximum of x */
};

/*!
 * \brief Adds a value to the statistical accumulator.
 * \details The sac_add functional operator adds a value to the accumulator.
 * The statistics are updated to reflect the new data value.
 * \param sac Pointer to statistical accumulator structure, mutable.
 * \param x Value to add to the accumulator.
 * \return Pointer to the updated statistical accumulator structure.
 */
static inline struct statistical_accumulator *sac_add(struct statistical_accumulator *sac, sac_scalar_t x) {
    // Update the counter, the sum of X, the sum of X squared, and the
    // minimum and maximum values.
    sac->sigmaX += x;
    sac->sigmaX2 += x * x;
    if (++sac->n == 1) {
        sac->min = x;
        sac->max = x;
    } else {
        if (x < sac->min)
            sac->min = x;
        if (x > sac->max)
            sac->max = x;
    }
    return sac;
}

/*!
 * \brief Subtracts a value from the statistical accumulator.
 * \details The sac_sub functional operator subtracts a value from the
 * accumulator. This assumes that the given value has previously been added to
 * the accumulator with the sac_add function. The statistics are updated to reflect
 * the removal of the given value.
 *
 * The implementation does not modify the minimum and maximum. The
 * values returned by `sac_min` and `sac_max` are invalid when the `sac_sub`
 * function is used.
 * \param sac Pointer to statistical accumulator structure, mutable.
 * \param x Value to subtract from the accumulator.
 * \return Pointer to the updated statistical accumulator structure.
 */
static inline struct statistical_accumulator *sac_sub(struct statistical_accumulator *sac, sac_scalar_t x) {
    if (sac->n) {
        --sac->n;
        sac->sigmaX -= x;
        sac->sigmaX2 -= x * x;
        // Note: min and max are not updated on subtraction.
        // The min and max members are now invalid!
    }
    return sac;
}

/*!
 * \brief Clears the statistical accumulator.
 * \details The `sac_clear` function resets the accumulator to its initial
 * state, removing all previously added data values.
 * \param sac Pointer to statistical accumulator structure, mutable.
 * \return Pointer to the cleared statistical accumulator structure.
 */
static inline struct statistical_accumulator *sac_clear(struct statistical_accumulator *sac) {
    sac->n = 0;
    sac->sigmaX = 0;
    sac->sigmaX2 = 0;
    sac->min = SAC_NAN;
    sac->max = SAC_NAN;
    return sac;
}

/*!
 * \brief Retrieves the count of values in the statistical accumulator.
 * \details The `sac_count` function returns the number of values that have been
 * added to the accumulator, less the number of values that have been
 * subtracted.
 * \param sac Pointer to statistical accumulator structure, immutable.
 * \return Count of values in the accumulator.
 */
static inline sac_size_t sac_count(const struct statistical_accumulator *sac) { return sac->n; }

/*!
 * \brief Computes the average of values in the statistical accumulator.
 * \details The `sac_avg` function calculates the arithmetic mean (average) of
 * the values that have been added to the accumulator.
 * \param sac Pointer to statistical accumulator structure, immutable.
 * \return Average of values in the accumulator, or SAC_NAN if no values.
 * \note Returns SAC_NAN if no values have been added to the accumulator.
 */
static inline sac_scalar_t sac_avg(const struct statistical_accumulator *sac) {
    const sac_size_t n = sac->n;
    if (n == 0)
        return SAC_NAN;
    return sac->sigmaX / n;
}

/*!
 * \brief Computes the sample standard deviation of values in the statistical accumulator.
 * \details The `sac_st_dev` function calculates the sample standard deviation
 * of the values that have been added to the accumulator. The `sac_st_dev`
 * function assumes that the accumulated data are just a sample of the whole
 * population.
 * \param sac Pointer to statistical accumulator structure, immutable.
 * \return Sample standard deviation of values in the accumulator, or SAC_NAN if
 * fewer than two values.
 * \note Returns SAC_NAN if fewer than two values have been added to the accumulator.
 */
static inline sac_scalar_t sac_st_dev(const struct statistical_accumulator *sac) {
    const sac_size_t n = sac->n;
    if (n < 2)
        return SAC_NAN;
    const sac_scalar_t sigmaX = sac->sigmaX;
    return SAC_SQRT((sac->n * sac->sigmaX2 - sigmaX * sigmaX) / (n * (n - 1)));
}

/*!
 * \brief Computes the population standard deviation of values in the statistical accumulator.
 * \details The `sac_st_dev_p` function calculates the population standard
 * deviation of the values that have been added to the accumulator. The
 * `sac_st_dev_p` function assumes that the accumulated data represent the
 * entire population, not just a sample.
 * \param sac Pointer to statistical accumulator structure, immutable.
 * \return Population standard deviation of values in the accumulator, or SAC_NAN if
 * no values.
 * \note Returns SAC_NAN if no values have been added to the accumulator.
 */
static inline sac_scalar_t sac_st_dev_p(const struct statistical_accumulator *sac) {
    const sac_size_t n = sac->n;
    if (n < 1)
        return SAC_NAN;
    const sac_scalar_t sigmaX = sac->sigmaX;
    return SAC_SQRT((n * sac->sigmaX2 - sigmaX * sigmaX) / (n * n));
}

/*!
 * \brief Computes the population variance of values in the statistical accumulator.
 * \details The `sac_var` function calculates the population variance of the
 * values that have been added to the accumulator, i.e. population standard
 * deviation squared. The `sac_var` function assumes that the accumulated data
 * represent the entire population, not just a sample.
 * \param sac Pointer to statistical accumulator structure, immutable.
 * \return Population variance of values in the accumulator, or SAC_NAN if no values.
 * \note Returns SAC_NAN if no values have been added to the accumulator.
 */
static inline sac_scalar_t sac_var(const struct statistical_accumulator *sac) {
    const sac_size_t n = sac->n;
    if (n < 1)
        return SAC_NAN;
    const sac_scalar_t sigmaX = sac->sigmaX;
    return (n * sac->sigmaX2 - sigmaX * sigmaX) / (n * n);
}

/*!
 * \brief Retrieves the minimum value in the statistical accumulator.
 * \details The `sac_min` function returns the smallest number that has been
 * added to the accumulator.
 * \param sac Pointer to statistical accumulator structure, immutable.
 * \return Minimum value in the accumulator, or SAC_NAN if no values.
 * \note Returns SAC_NAN if no values have been added to the accumulator.
 */
static inline sac_scalar_t sac_min(const struct statistical_accumulator *sac) {
    if (sac->n == 0)
        return SAC_NAN;
    return sac->min;
}

/*!
 * \brief Retrieves the maximum value in the statistical accumulator.
 * \details The `sac_max` function returns the largest number that has been
 * added to the accumulator.
 * \param sac Pointer to statistical accumulator structure, immutable.
 * \return Maximum value in the accumulator, or SAC_NAN if no values.
 * \note Returns SAC_NAN if no values have been added to the accumulator.
 */
static inline sac_scalar_t sac_max(const struct statistical_accumulator *sac) {
    if (sac->n == 0)
        return SAC_NAN;
    return sac->max;
}

#endif /* SAC_H */
