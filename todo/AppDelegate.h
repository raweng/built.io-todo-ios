//
//  AppDelegate.h
//  todo
//
//  Created by Akshay Mhatre on 29/10/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>
@property (strong, nonatomic) BuiltApplication * builtApplication;
@property (strong, nonatomic) UIWindow *window;
+(AppDelegate*)sharedApplication;
@end
