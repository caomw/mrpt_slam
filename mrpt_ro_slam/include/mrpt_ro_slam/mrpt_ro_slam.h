/***********************************************************************************
 * Revised BSD License                                                             *
 * Copyright (c) 2014, Markus Bader <markus.bader@tuwien.ac.at>                    *
 * All rights reserved.                                                            *
 *                                                                                 *
 * Redistribution and use in source and binary forms, with or without              *
 * modification, are permitted provided that the following conditions are met:     *
 *     * Redistributions of source code must retain the above copyright            *
 *       notice, this list of conditions and the following disclaimer.             *
 *     * Redistributions in binary form must reproduce the above copyright         *
 *       notice, this list of conditions and the following disclaimer in the       *
 *       documentation and/or other materials provided with the distribution.      *
 *     * Neither the name of the Vienna University of Technology nor the           *
 *       names of its contributors may be used to endorse or promote products      *
 *       derived from this software without specific prior written permission.     *
 *                                                                                 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND *
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          *
 * DISCLAIMED. IN NO EVENT SHALL Markus Bader BE LIABLE FOR ANY                    *
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES      *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;    *
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND     *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS   *
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                    *                       *
 ***********************************************************************************/

#ifndef MRPT_RO_SLAM_H
#define MRPT_RO_SLAM_H

#include <iostream>
#include <stdint.h>
#include <mrpt_ro_slam/mrpt_ro_slam_core.h>
#include <mrpt/utils/CConfigFile.h>
#include <mrpt/gui/CDisplayWindow3D.h>
#include <mrpt/slam/CMetricMapBuilderRBPF.h>
#include <mrpt/opengl/CEllipsoid.h>

#include <mrpt/version.h>
#if MRPT_VERSION>=0x130
#	include <mrpt/obs/CActionRobotMovement2D.h>
#	include <mrpt/obs/CActionRobotMovement3D.h>
	using namespace mrpt::maps;
	using namespace mrpt::obs;
#else
#	include <mrpt/slam/CActionRobotMovement2D.h>
#	include <mrpt/slam/CActionRobotMovement3D.h>
	using namespace mrpt::slam;
#endif


class RBPFSlam : public RBPFSlamCore {
public:
    struct Parameters {
        Parameters(RBPFSlam *p);
        bool debug;
        bool gui_mrpt;
        std::string iniFile;
        std::string mapFile;
		std::string sensorSources; //!< A list of topics (e.g. laser scanners) to subscribe to for sensory data. Split with "," (e.g. "laser1,laser2")
        bool *use_motion_model_default_options;
		CActionRobotMovement2D::TMotionModelOptions *motion_model_options;
		CActionRobotMovement2D::TMotionModelOptions *motion_model_default_options;
    };
    RBPFSlam (Parameters *param);
    ~RBPFSlam();
protected:
    Parameters *param_;
    void init();
    void init3DDebug();
	void show3DDebug(CSensoryFramePtr _observations);
    void configureMapBuilder(const mrpt::utils::CConfigFile &_configFile);
    //virtual bool waitForMap(){return false;};

    mrpt::gui::CDisplayWindow3DPtr win3D_;
    mrpt::opengl::COpenGLScenePtr scene_;
	mrpt::slam::CMetricMapBuilderRBPF::TConstructionOptions rbpfMappingOptions;
	mrpt::slam::CMetricMapBuilderRBPF * mapBuilderRBPF;
	mrpt::opengl::CSetOfObjectsPtr objs;

    int         SCENE3D_FREQ_;
    bool        SCENE3D_FOLLOW_;
    bool        SHOW_PROGRESS_3D_REAL_TIME_;
    int         SHOW_PROGRESS_3D_REAL_TIME_DELAY_MS_;
	float 		t_exec;

};

#endif // MRPT_RO_SLAM_H
