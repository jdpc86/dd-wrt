/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


/**
 * @defgroup fal_sec FAL_SEC
 * @{
 */
#include "sw.h"
#include "fal_sec.h"
#include "hsl_api.h"

static sw_error_t
_fal_sec_norm_item_set(a_uint32_t dev_id, fal_norm_item_t item, void *value)
{
    sw_error_t rv;
    hsl_api_t *p_api;

    SW_RTN_ON_NULL(p_api = hsl_api_ptr_get(dev_id));

    if (NULL == p_api->sec_norm_item_set)
        return SW_NOT_SUPPORTED;

    rv = p_api->sec_norm_item_set(dev_id, item, value);
    return rv;
}

static sw_error_t
_fal_sec_norm_item_get(a_uint32_t dev_id, fal_norm_item_t item, void *value)
{
    sw_error_t rv;
    hsl_api_t *p_api;

    SW_RTN_ON_NULL(p_api = hsl_api_ptr_get(dev_id));

    if (NULL == p_api->sec_norm_item_get)
        return SW_NOT_SUPPORTED;

    rv = p_api->sec_norm_item_get(dev_id, item, value);
    return rv;
}

/**
 * @brief Set normalization particular item types value.
 * @details   Comments:
 *       This operation will set normalization item values on a particular device.
 *       The prototye of value based on the item type.
 * @param[in] dev_id device id
 * @param[in] item normalizaton item type
 * @param[in] value normalizaton item value
 * @return SW_OK or error code
 */
sw_error_t
fal_sec_norm_item_set(a_uint32_t dev_id, fal_norm_item_t item, void *value)
{
    sw_error_t rv;

    FAL_API_LOCK;
    rv = _fal_sec_norm_item_set(dev_id, item, value);
    FAL_API_UNLOCK;
    return rv;
}

/**
 * @brief Get normalization particular item types value.
 * @details   Comments:
 *       This operation will set normalization item values on a particular device.
 *       The prototye of value based on the item type.
 * @param[in] dev_id device id
 * @param[in] item normalizaton item type
 * @param[out] value normalizaton item value
 * @return SW_OK or error code
 */
sw_error_t
fal_sec_norm_item_get(a_uint32_t dev_id, fal_norm_item_t item, void *value)
{
    sw_error_t rv;

    FAL_API_LOCK;
    rv = _fal_sec_norm_item_get(dev_id, item, value);
    FAL_API_UNLOCK;
    return rv;
}

/**
 * @}
 */
