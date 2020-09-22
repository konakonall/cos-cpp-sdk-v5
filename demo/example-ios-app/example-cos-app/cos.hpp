//
//  cos.hpp
//  example-cos-app
//
//  Created by wjielai on 2020/9/17.
//

#ifndef cos_hpp
#define cos_hpp

#include <stdio.h>
#include <string>

void getService(std::string configFilePath);
void getObject(std::string configFilePath, std::string localFilePath);
void putObject(std::string configFilePath, std::string localFilePath);

#endif /* cos_hpp */
