/* -------------------------------------------------------------------------- *
 *                         OpenSim:  testCopyProperties.cpp                   *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2016 Stanford University and the Authors                *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

#include <OpenSim/OpenSim.h>

using namespace OpenSim;
using namespace std;

int main() {
    try {
        Model m("arm26.osim");
        m.initSystem();
        Model modelCopy(m);
        modelCopy.updForceSet().setSize(0);
        for (const auto& thelenMusc : m.getComponentList<OpenSim::Thelen2003Muscle>()) {
            Millard2012EquilibriumMuscle millardMusc;
            const GeometryPath& gp = thelenMusc.get_GeometryPath();
            std::cout << gp.dump() << std::endl;
            millardMusc.copyPropertiesFromObject(thelenMusc);
            millardMusc.setName(thelenMusc.getName());
            modelCopy.updForceSet().cloneAndAppend(millardMusc);
        }
        modelCopy.print("arm26MillardEq.osim");
    }
    catch (const Exception& e) {
        e.print(cerr);
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}
