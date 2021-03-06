#ifndef TEST_FIXTURE_ADGPRS_H
#define TEST_FIXTURE_ADGPRS_H

#include <gtest/gtest.h>
#include <QString>
#include <iostream>
#include "Utilities/file_handling/filehandling.h"
#include "GTest/Model/test_fixture_model_base.h"

class AdgprsTestFixture : public ModelBaseTest {
protected:
    AdgprsTestFixture(){
        settings_ = new Utilities::Settings::Settings(fo_driver_path_, output_directory_);
        settings_->simulator()->set_driver_file_path(sim_driver_path_);
        settings_->model()->set_reservoir_grid_path(reservoir_grid_path_);
        model_ = new Model::Model(*settings_->model());
    }
    QString sim_driver_path_ = Utilities::FileHandling::GetBuildDirectoryPath() + "/../examples/ADGPRS/5spot/5SPOT.gprs";
    QString fo_driver_path_ = Utilities::FileHandling::GetBuildDirectoryPath() + "/../examples/ADGPRS/5spot/5spot_fieldopt_driver.json";
    QString output_directory_ = "/home/einar/Documents/GitHub/PCG/fieldopt_output/adgprs";
    QString reservoir_grid_path_ = Utilities::FileHandling::GetBuildDirectoryPath() + "/../examples/ADGPRS/5spot/ECL_5SPOT.EGRID";
    QString json_summary_path_ = Utilities::FileHandling::GetBuildDirectoryPath() + "/../examples/ADGPRS/5spot/5SPOT.json";
    QString hdf5_summary_path_ = Utilities::FileHandling::GetBuildDirectoryPath() + "/../examples/ADGPRS/5spot/5SPOT.SIM.H5";
    QString base_summary_path_ = Utilities::FileHandling::GetBuildDirectoryPath() + "/../examples/ADGPRS/5spot/5SPOT";
};

#endif // TEST_FIXTURE_ADGPRS_H
