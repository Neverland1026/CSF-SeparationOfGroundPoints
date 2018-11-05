// ======================================================================================
// Copyright 2017 State Key Laboratory of Remote Sensing Science, 
// Institute of Remote Sensing Science and Engineering, Beijing Normal University

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ======================================================================================


#include <vector>
#include "Cfg.h"
#include "../src/CSF.h" 
#include <locale.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
	CSF csf;
	//step 1 输入点云
	string terr_pointClouds_filepath = "TEST.txt";
	csf.readPointsFromFile(terr_pointClouds_filepath);

	clock_t start, end;
	start = clock();

	//step 2 设置参数
	string class_threshold = "0.5";
	string cloth_resolution = "1";
	string iterations = "500";
	string rigidness = "3";
	string time_step = "0.65";
	csf.params.bSloopSmooth = true/*ss*/;
	csf.params.class_threshold = atof(class_threshold.c_str());
	csf.params.cloth_resolution = atof(cloth_resolution.c_str());
	csf.params.interations = atoi(iterations.c_str());
	csf.params.rigidness = atoi(rigidness.c_str());
	csf.params.time_step = atof(time_step.c_str());

	//step3 执行滤波,result中储存的是地面点的索引 
	std::vector<int> groundIndexes, offGroundIndexes;
	csf.do_filtering(groundIndexes, offGroundIndexes, true);
	//csf.do_filtering(groundIndexes, offGroundIndexes, false);

	end = clock();
	double dur = (double)(end - start);
	printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));

	csf.savePoints(groundIndexes, "ground.txt");
	csf.savePoints(offGroundIndexes, "non-ground.txt");

	return 0;
}