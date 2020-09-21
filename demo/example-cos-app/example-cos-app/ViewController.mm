//
//  ViewController.m
//  example-cos-app
//
//  Created by wjielai on 2020/9/17.
//

#import "ViewController.h"
#include "cos.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    NSString* configJson = [[NSBundle mainBundle] pathForResource:@"config" ofType:@"json"];
    std::string configPath = std::string([configJson UTF8String]);
    
    getService(configPath);
    
    NSString* localTempPath = [NSString pathWithComponents:@[NSTemporaryDirectory(), @"example"]];
    std::string tempPath = std::string([localTempPath UTF8String]);
    
    getObject(configPath, tempPath);
    
    putObject(configPath, tempPath);
}


@end
