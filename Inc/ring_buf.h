/* SPDX-License-Identifier: MIT */
/*!
 * \file ring_buf.h
 * \copyright Roy Ratcliffe, Northumberland, United Kingdom
 *
 * Permission is hereby granted, free of charge,  to any person obtaining a
 * copy  of  this  software  and    associated   documentation  files  (the
 * "Software"), to deal in  the   Software  without  restriction, including
 * without limitation the rights to  use,   copy,  modify,  merge, publish,
 * distribute, sublicense, and/or sell  copies  of   the  Software,  and to
 * permit persons to whom the Software is   furnished  to do so, subject to
 * the following conditions:
 *
 *     The above copyright notice and this permission notice shall be
 *     included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY OF ANY KIND, EXPRESS
 * OR  IMPLIED,  INCLUDING  BUT  NOT   LIMITED    TO   THE   WARRANTIES  OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR   PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS  OR   COPYRIGHT  HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY,  WHETHER   IN  AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM,  OUT  OF   OR  IN  CONNECTION  WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>

/*!
 * \brief Error code for message too long.
 * \details Some embedded kits do not define `EMSGSIZE`, the "message too long"
 * error code. The standard C `<errno.h>` header normally defines it. The
 * value is not consistent across operating systems. Its value may be 90,
 * 122, or some other high value. The actual value matters for error number
 * to error string conversions. The value cannot be any integer value. It
 * must map to a valid error string. Consequently, deal with a missing
 * error define by mapping the error to another existing error that carries
 * a similar meaning.
 *
 * This code maps `EMSGSIZE` to `ENOMEM` if `EMSGSIZE` is not defined.
 * This is a workaround for systems that do not define `EMSGSIZE`.
 */
#ifndef EMSGSIZE
#define EMSGSIZE ENOMEM
#endif

/*!
 * \brief Ring buffer pointer difference type.
 * \details The ring buffer pointer difference type uses a signed integer to
 * represent the difference between two pointers within the buffer.
 */
typedef ptrdiff_t ring_buf_ptrdiff_t;

/*!
 * \brief Ring buffer size type.
 * \details The ring buffer size type uses an unsigned integer to represent the
 * size of the ring buffer.
 */
typedef size_t ring_buf_size_t;

/*!
 * \brief Maximum ring buffer size.
 * \details This macro defines the maximum size of a ring buffer.
 * It uses the minimum value of a signed pointer difference type to ensure
 * that the size can accommodate the largest possible ring buffer.
 */
#define RING_BUF_SIZE_MAX ((ring_buf_size_t)PTRDIFF_MIN)

/*!
 * \defgroup ring_buf_zone Ring Buffer Zone
 * \ingroup ring_buf_zone
 * \{
 */

/*!
 * \brief Ring buffer zone structure.
 * \details This structure needs to exist within the header.
 * It defines a zone within the ring buffer that tracks the base, head, and tail
 * pointers. The base pointer represents the starting point of the zone, while
 * the head pointer represents the current position for acknowledged data, and the
 * tail pointer represents the current position for claimed data.
 * \sa ring_buf_zone_reset
 * \note The base, head, and tail pointers are all of type `ring_buf_ptrdiff_t`,
 * which is a signed integer type. This allows for negative values, which can be
 * useful for certain buffer operations.
 */
struct ring_buf_zone {
    ring_buf_ptrdiff_t base, head, tail;
};

/*!
 * \}
 */

/*!
 * \defgroup ring_buf Ring Buffer
 * \ingroup ring_buf
 * \{
 */

/*!
 * \brief Ring buffer instance.
 * \details This structure represents a ring buffer. It contains a pointer to
 * the buffer space, the size of the buffer, and two zones: one for putting
 * data into the buffer and another for getting data from the buffer.
 */
struct ring_buf {
    void *space;
    ring_buf_size_t size;
    struct ring_buf_zone put, get;
};

static inline ring_buf_size_t ring_buf_used_space(const struct ring_buf *buf) { return buf->put.tail - buf->get.head; }

static inline bool ring_buf_is_empty(const struct ring_buf *buf) { return ring_buf_used_space(buf) == 0U; }

static inline ring_buf_size_t ring_buf_free_space(const struct ring_buf *buf) {
    return buf->size - (buf->put.head - buf->get.tail);
}

static inline bool ring_buf_is_full(const struct ring_buf *buf) { return ring_buf_free_space(buf) == 0U; }

void ring_buf_reset(struct ring_buf *buf, ring_buf_ptrdiff_t base);

/*!
 * \defgroup ring_buf_contiguous Contiguous Ring Buffer Access
 * \details This group provides functions for accessing ring buffers that may
 * only contain contiguous data. The functions allow for reading and writing
 * data in a way that requires the data to be contiguous in memory.
 * \ingroup ring_buf_contiguous
 * \{
 */

/*!
 * \brief Claims space for putting data into a ring buffer.
 * \details Claims contiguous space. Advances the "put" head.
 * One put operation starts with a claim. A successful claim expands the "put
 * zone" by the requested number of bytes.
 */
ring_buf_size_t ring_buf_put_claim(struct ring_buf *buf, void **space, ring_buf_size_t size);

/*!
 * \brief Acknowledges space claimed for putting data into a ring buffer.
 * \details Acknowledging the same number of bytes advances the put zone. Notice
 * that the claim cannot span across the end of the buffer space. Buffer size
 * less the put zone's head \e clamps the claim size. It \e cannot exceed the
 * remaining contiguous space.
 * \param buf Ring buffer address.
 * \param size Number of bytes to acknowledge.
 * \retval 0 on successful put.
 * \retval -EINVAL if \c size exceeds previously claimed aggregate space.
 */
int ring_buf_put_ack(struct ring_buf *buf, ring_buf_size_t size);

/*!
 * \brief Claims contiguous space for getting.
 * \details Advances the "get" head.
 */
ring_buf_size_t ring_buf_get_claim(struct ring_buf *buf, void **space, ring_buf_size_t size);

/*!
 * \brief Acknowledges space claimed for getting data from a ring buffer.
 * \details Acknowledging the same number of bytes advances the get zone.
 * Notice that the claim cannot span across the end of the buffer space.
 * Buffer size less the get zone's head \e clamps the claim size. It \e cannot
 * exceed the remaining contiguous space.
 * \param buf Ring buffer address.
 * \param size Number of bytes to acknowledge.
 * \retval 0 on successful get.
 * \retval -EINVAL if \c size exceeds previously claimed aggregate space.
 */
int ring_buf_get_ack(struct ring_buf *buf, ring_buf_size_t size);

/*!
 * \}
 */

/*!
 * \defgroup ring_buf_discontiguous Discontiguous Ring Buffer Access
 * \details This group provides functions for accessing ring buffers that may
 * contain discontiguous data. The functions allow for reading and writing
 * data in a way that does not require the data to be contiguous in memory.
 * \ingroup ring_buf_discontiguous
 * \{
 */

/*!
 * \brief Puts non-contiguous bytes into the ring buffer.
 * \details The return value may be less than the given size if the buffer runs
 * out of free space.
 * \note Does \e not automatically acknowledge the space.
 * \param buf Ring buffer.
 * \param data Address of bytes to put.
 * \param size Number of bytes to put.
 * \returns Buffer space to acknowledge in bytes.
 * \note Does \e not automatically acknowledge the space.
 */
ring_buf_size_t ring_buf_put(struct ring_buf *buf, const void *data, ring_buf_size_t size);

/*!
 * \brief Gets data from a ring buffer.
 * \details Copies discontinuous data.
 * \param data Address of copied data, or \c NULL to ignore.
 * \param size Number of bytes to get.
 * \returns Number of bytes to acknowledge.
 * \note Does \e not automatically acknowledge the space.
 */
ring_buf_size_t ring_buf_get(struct ring_buf *buf, void *data, ring_buf_size_t size);

/*!
 * \brief Puts all or none.
 * \details If the ring buffer does not have enough space, the operation fails
 * and no data is written.
 * \param buf Ring buffer.
 * \param data Address of bytes to put.
 * \param size Number of bytes to put.
 * \returns 0 on success, or -EMSGSIZE if the buffer does not have enough space.
 * \note Automatically acknowledges the space.
 */
int ring_buf_put_all(struct ring_buf *buf, const void *data, ring_buf_size_t size);

/*!
 * \brief Gets all or none.
 * \details If the ring buffer does not have enough space, the operation fails
 * and no data is read.
 * \param buf Ring buffer.
 * \param data Address of bytes to get.
 * \param size Number of bytes to get.
 * \returns 0 on success, or -EAGAIN if the buffer does not have enough space.
 * \note Automatically acknowledges the space.
 */
int ring_buf_get_all(struct ring_buf *buf, void *data, ring_buf_size_t size);

/*!
 * \}
 */

/*
 * for uint8_t
 */
#include <stdint.h>

/*!
 * \brief Defines a static ring buffer.
 * \details This macro defines a static ring buffer with a specified name and size.
 * It allocates a static array of bytes to serve as the buffer space and initialises
 * the ring buffer structure.
 * \param _name_ Name of the ring buffer.
 * \param _size_ Size of the ring buffer in bytes.
 */
#define RING_BUF_DEFINE(_name_, _size_)                                                                                \
    static uint8_t _ring_buf_space_##_name_[_size_];                                                                   \
    static struct ring_buf _name_ = {.space = _ring_buf_space_##_name_, .size = _size_}

/*!
 * \}
 */

#ifdef __cplusplus
}
#endif
