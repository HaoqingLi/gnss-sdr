/*!
 * \file dll_pll_robust_conf.h
 * \brief Class that contains all the configuration parameters for generic tracking block based on a DLL and a PLL.
 * \author Javier Arribas, 2018. jarribas(at)cttc.es
 *
 * Class that contains all the configuration parameters for generic tracking block based on a DLL and a PLL.
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2019  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_DLL_PLL_ROBUST_CONF_H
#define GNSS_SDR_DLL_PLL_ROBUST_CONF_H

#include "configuration_interface.h"
#include <cstdint>
#include <string>

class Dll_Pll_robust_Conf
{
public:
    Dll_Pll_robust_Conf();
    void SetFromConfiguration(ConfigurationInterface *configuration, const std::string &role);

    /* DLL/PLL tracking configuration */
    int32_t fll_filter_order;
    bool enable_fll_pull_in;
    bool enable_fll_steady_state;
    uint32_t pull_in_time_s;
    uint32_t bit_synchronization_time_limit_s;
    int32_t pll_filter_order;
    int32_t dll_filter_order;
    double fs_in;
    uint32_t vector_length;
    bool dump;
    bool dump_mat;
    std::string dump_filename;
    float pll_pull_in_bw_hz;
    float dll_pull_in_bw_hz;
    float fll_bw_hz;
    float pll_bw_hz;
    float dll_bw_hz;
    float pll_bw_narrow_hz;
    float dll_bw_narrow_hz;
    float early_late_space_chips;
    float very_early_late_space_chips;
    float early_late_space_narrow_chips;
    float very_early_late_space_narrow_chips;
    float slope;
    float spc;
    float y_intercept;
    float myriad_para;
    float huber_tunning;
    int32_t extend_correlation_symbols;
    bool carrier_aiding;
    bool high_dyn;
    std::string item_type;
    std::string time_method;
    std::string frequency_method;
    int32_t cn0_samples;
    int32_t cn0_smoother_samples;
    float cn0_smoother_alpha;
    int32_t carrier_lock_test_smoother_samples;
    float carrier_lock_test_smoother_alpha;
    int32_t cn0_min;
    int32_t max_code_lock_fail;
    int32_t max_carrier_lock_fail;
    uint32_t smoother_length;
    double carrier_lock_th;
    bool track_pilot;
    bool enable_doppler_correction;
    char system;
    char signal[3]{};
};

#endif
