/*!
 * \file gps_l1_ca_pcps_acquisition_fine_doppler.h
 * \brief Adapts a PCPS acquisition block with fine Doppler estimation to an AcquisitionInterface for
 *  GPS L1 C/A signals
 * \authors <ul>
 *          <li> Javier Arribas, 2013. jarribas(at)cttc.es
 *          </ul> *
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

#ifndef GNSS_SDR_GPS_L1_CA_PCPS_ACQUISITION_FINE_DOPPLER_H
#define GNSS_SDR_GPS_L1_CA_PCPS_ACQUISITION_FINE_DOPPLER_H

#include "channel_fsm.h"
#include "gnss_synchro.h"
#include "pcps_acquisition_fine_doppler_cc.h"
#include <memory>
#include <string>
#include <vector>
#if GNURADIO_USES_STD_POINTERS
using pcps_acquisition_fine_doppler_cc_sptr = std::shared_ptr<pcps_acquisition_fine_doppler_cc>;
#else
#include <boost/shared_ptr.hpp>
using pcps_acquisition_fine_doppler_cc_sptr = boost::shared_ptr<pcps_acquisition_fine_doppler_cc>;
#endif

class ConfigurationInterface;

/*!
 * \brief This class Adapts a PCPS acquisition block with fine Doppler estimation to an AcquisitionInterface for
 *  GPS L1 C/A signals
 */
class GpsL1CaPcpsAcquisitionFineDoppler : public AcquisitionInterface
{
public:
    GpsL1CaPcpsAcquisitionFineDoppler(ConfigurationInterface* configuration,
        const std::string& role,
        unsigned int in_streams,
        unsigned int out_streams);

    ~GpsL1CaPcpsAcquisitionFineDoppler() = default;

    inline std::string role() override
    {
        return role_;
    }

    /*!
     * \brief Returns "GPS_L1_CA_PCPS_Acquisition_Fine_Doppler"
     */
    inline std::string implementation() override
    {
        return "GPS_L1_CA_PCPS_Acquisition_Fine_Doppler";
    }

    inline size_t item_size() override
    {
        return item_size_;
    }

#if GNURADIO_USES_STD_POINTERS
    void connect(std::shared_ptr<gr::top_block> top_block) override;
    void disconnect(std::shared_ptr<gr::top_block> top_block) override;
    std::shared_ptr<gr::basic_block> get_left_block() override;
    std::shared_ptr<gr::basic_block> get_right_block() override;
#else
    void connect(boost::shared_ptr<gr::top_block> top_block) override;
    void disconnect(boost::shared_ptr<gr::top_block> top_block) override;
    boost::shared_ptr<gr::basic_block> get_left_block() override;
    boost::shared_ptr<gr::basic_block> get_right_block() override;
#endif
    /*!
     * \brief Set acquisition/tracking common Gnss_Synchro object pointer
     * to efficiently exchange synchronization data between acquisition and
     *  tracking blocks
     */
    void set_gnss_synchro(Gnss_Synchro* p_gnss_synchro) override;

    /*!
     * \brief Set acquisition channel unique ID
     */
    inline void set_channel(unsigned int channel) override
    {
        channel_ = channel;
        acquisition_cc_->set_channel(channel_);
    }

    /*!
     * \brief Set channel fsm associated to this acquisition instance
     */
    inline void set_channel_fsm(std::weak_ptr<ChannelFsm> channel_fsm) override
    {
        channel_fsm_ = channel_fsm;
        acquisition_cc_->set_channel_fsm(channel_fsm);
    }

    /*!
     * \brief Set statistics threshold of PCPS algorithm
     */
    void set_threshold(float threshold) override;

    /*!
     * \brief Set maximum Doppler off grid search
     */
    void set_doppler_max(unsigned int doppler_max) override;

    /*!
     * \brief Set Doppler steps for the grid search
     */
    void set_doppler_step(unsigned int doppler_step) override;

    /*!
     * \brief Initializes acquisition algorithm.
     */
    void init() override;

    void set_local_code() override;

    /*!
     * \brief Returns the maximum peak of grid search
     */
    signed int mag() override;

    /*!
     * \brief Restart acquisition algorithm
     */
    void reset() override;

    /*!
     * \brief If state = 1, it forces the block to start acquiring from the first sample
     */
    void set_state(int state) override;

    /*!
     * \brief Stop running acquisition
     */
    void stop_acquisition() override;

    void set_resampler_latency(uint32_t latency_samples __attribute__((unused))) override{};

private:
    pcps_acquisition_fine_doppler_cc_sptr acquisition_cc_;
    size_t item_size_;
    std::string item_type_;
    unsigned int vector_length_;
    unsigned int channel_;
    std::weak_ptr<ChannelFsm> channel_fsm_;
    float threshold_;
    int doppler_max_;
    unsigned int doppler_step_;
    unsigned int sampled_ms_;
    int max_dwells_;
    int64_t fs_in_;
    bool dump_;
    std::string dump_filename_;
    std::vector<std::complex<float>> code_;
    Gnss_Synchro* gnss_synchro_;
    std::string role_;
    unsigned int in_streams_;
    unsigned int out_streams_;
};

#endif  // GNSS_SDR_GPS_L1_CA_PCPS_ACQUISITION_FINE_DOPPLER_H
