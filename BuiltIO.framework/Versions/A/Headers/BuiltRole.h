//
//  BuiltRole.h
//  builtDemo
//
//  Created by Akshay Mhatre on 23/03/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BuiltUser.h"
#import "RoleObject.h"

/** Roles are a sort of group containing users and other roles. So instead of giving permission to each user, could instead add those users to and assign permissions to the role. 
 All users in the role would inherit permissions that the role receives.
 */
@interface BuiltRole : NSObject

/**---------------------------------------------------------------------------------------
 * @name Create a BuiltRole Object.
 *  ---------------------------------------------------------------------------------------
 */
/**
 @abstract Initializes a `BuiltRole` Object.
 */
+ (BuiltRole *)role;

/**
    @abstract Creates a `RoleObject` with specified name.
    @param roleName Role name for creating a `RoleObject` with.
 */
+ (RoleObject *)createRoleWithName:(NSString *)roleName;


/**---------------------------------------------------------------------------------------
 * @name Attaching/Removing Headers.
 *  ---------------------------------------------------------------------------------------
 */

/**
 @abstract Additional headers if required
 
 @param header header value
 @param key header key
 */
- (void)setHeader:(NSString *)header forKey:(NSString *)key;

/**
 @abstract Remove a header for a specific key
 @param key key for which to remove the header value
 */
- (void)removeHeaderForKey:(NSString *)key;

/**
    @abstract If you require to fetch roles belonging to some other application, you can use this method to set the app parameters.
    @param apiKey api key of the app.
    @param uid appuid of the app.
 */
- (void)setApplicationApiKey:(NSString *)apiKey andUid:(NSString *)uid;


/**---------------------------------------------------------------------------------------
 * @name Fetch RoleObject
 *  ---------------------------------------------------------------------------------------
 */
/**
    @abstract Fetches and returns all Roles in the application.
    @param successBlock Returns array of `RoleObject`s in callback.
    @param errorBlock Reports an error in callback.
 */
- (void)fetchRolesOnSuccess:(void(^) (NSMutableArray *rolesObjects))successBlock onError:(void(^) (NSError *error))errorBlock;

/**
    @abstract Get `RoleObject` with the name specified.
    @discussion after using fetchRolesOnSuccess:successBlock:onError method, call this method with the role name to retrieve the `RoleObject`s
    @param rolename Role name
    @param successBlock Returns the `RoleObject` with specified name if it exists.
    @param errorBlock Reports an error in callback.
 */
- (void)getRole:(NSString *)rolename onSuccess:(void (^)(RoleObject *roleObject))successBlock onError:(void (^)(NSError *error))errorBlock;

/**
    @abstract Returns the count of all Roles in application.
    @discussion after using fetchRolesOnSuccess:successBlock:onError method, call this method to get the number of roles.
    @return Count of Roles in application.
 */
- (NSInteger)count;

/**
    @abstract Checks whether a role with specified name exists in application.
    @discussion after using fetchRolesOnSuccess:successBlock:onError method, call this method with the role name to check whether the role exists.
    @param rolename Role name.
    @return Returns whether the role exists or not.
 */
- (BOOL)hasRole:(NSString *)rolename;

@end
