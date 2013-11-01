//
//  AppDelegate.m
//  todo
//
//  Created by Akshay Mhatre on 29/10/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import "AppDelegate.h"
#import <BuiltIO/BuiltIO.h>
#import "TasksViewController.h"

@interface AppDelegate()<BuiltUIGoogleAppSettingDelegate, BuiltUILoginDelegate>{

}

@property (nonatomic, strong) UINavigationController *nc;

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    
    [Built initializeWithApiKey:@"bltad1e7e5f0cabdd5a"
                         andUid:@"todoapp"];
    
    BuiltUser *user = [BuiltUser getSession];
    if (user) {
        [BuiltUser setCurrentUser:user];
        [self loadTasks];
    }else{
        BuiltUILoginController *loginController = [[BuiltUILoginController alloc]init];
        loginController.fields = BuiltLoginFieldGoogle | BuiltLoginFieldUsernameAndPassword | BuiltLoginFieldLogin;
        loginController.googleAppSettingDelegate = self;
        loginController.delegate = self;
        loginController.shouldHandleLoadingHUD = YES;
        [loginController.logoImageView setImage:[UIImage imageNamed:@"todo-logo"]];

        self.nc = [[UINavigationController alloc]initWithRootViewController:loginController];
        
        self.window.backgroundColor = [UIColor whiteColor];
        [self.window setRootViewController:_nc];
    }

    [self.window makeKeyAndVisible];
    
    return YES;
}

- (void)loadTasks{
    TasksViewController *tasks = [[TasksViewController alloc]initWithStyle:UITableViewStylePlain withClassUID:@"todo_task"];
    if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"7.0")) {
        [tasks setEdgesForExtendedLayout:UIRectEdgeNone];
    }
    [self.nc.navigationBar setTranslucent:YES];
    self.nc = [[UINavigationController alloc]initWithRootViewController:tasks];
    [self.window setRootViewController:self.nc];
}

- (NSString*)googleAppClientID {
    return @"433785026559.apps.googleusercontent.com";
}

- (NSString*)googleAppClientSecret {
    return @"C0scrv2bJPJsYEMADKWRiGLQ";
}

-(void)loginSuccessWithUser:(BuiltUser *)user{
    [BuiltUser setCurrentUser:user];
    [user saveSession];
    [self loadTasks];
}

-(void)loginFailedWithError:(NSError *)error{

}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
