//
//  RoleObject.h
//  builtDemo
//
//  Created by Samir Bhide on 26/03/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import <Foundation/Foundation.h>
/** RoleObject is individual role object that is created at application level. Using properties and methods of RoleObject. */
@interface RoleObject : NSObject

/**---------------------------------------------------------------------------------------
 * @name Role Specific Properties
 *  ---------------------------------------------------------------------------------------
 */
/**
 Gets or sets the name for a role. This value must be set before the role
 has been saved to the server, and cannot be set once the role has been
 saved.
 A role's name can only contain alphanumeric characters, _, -, and spaces.
 */
@property(nonatomic, strong) NSString *name;

/**
 Gets or sets the UID for a role. This value must be set before the role
 has been saved to the server, and cannot be set once the role has been
 saved.
 A role's name can only contain alphanumeric characters, _, -, and spaces.
 */
@property(nonatomic, strong) NSString *roleUID;

/**
 Array of users that are included in a `BuiltRole`.
 */
@property(nonatomic, strong) NSMutableArray *users;

/**
 Array of other roles that are included in a `BuiltRole`.
 */
@property(nonatomic, strong) NSMutableArray *roles;

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
    @abstract If you require to create/retrieve/update a role belonging to some other application, you can use this method to set the app parameters.
    @param apiKey api key of the app.
    @param uid appuid of the app.
 */
- (void)setApplicationApiKey:(NSString *)apiKey andUid:(NSString *)uid;

/**---------------------------------------------------------------------------------------
 * @name Editing Roles
 *  ---------------------------------------------------------------------------------------
 */

/**
    @abstract Adds a user to a role
    @param userUID User's UID that needs to be added to role.
 */
- (void)addUser:(NSString *)userUID;


/**
    @abstract Removes a user from a role
    @param userUID User's UID that needs to be removed from role.
 */
- (void)removeUser:(NSString *)userUID;

/**
    @abstract Adds a subrole to current `RoleObject`.
    @param roleUID Role UID that has to be added as a subrole.
 */
- (void)addRole:(NSString *)roleUID;


/**
    @abstract Removes a subrole from current `RoleObject` if it exists.
    @param roleUID Role UID that has to be added as a subrole.
 */
- (void)removeRole:(NSString *)roleUID;

/**
    @abstract Saves the modified `RoleObject`
    @param successBlock Success callback.
    @param errorBlock Error callback.
 */
- (void)saveOnSuccess:(void (^) (void))successBlock onError:(void (^) (NSError *error))errorBlock;

/**
    @abstract Deletes the `RoleObject`
    @param successBlock Success callback.
    @param errorBlock Error callback.
 */
- (void)destroyOnSuccess:(void (^) (void))successBlock onError:(void (^)(NSError *error))errorBlock;


/**---------------------------------------------------------------------------------------
 * @name Role Helper Methods
 *  ---------------------------------------------------------------------------------------
 */
/**
    @abstract Checks whether a user with user uid exists in role.
    @param user_uid User UID to check for existence in role.
    @return Returns whether the user in role exists or not.
 */
- (BOOL)hasUser:(NSString *)user_uid;

/**
    @abstract Checks whether a role with specified name exists in role.
    @param roleUID Role UID of a sub role to check for existence in role.
    @return returns whether the role exists or not.
 */
- (BOOL)hasRole:(NSString *)roleUID;

/**
    @abstract Returns the subroles contained in a role. Subroles are a subset of `RoleObject`.
    @return Array of Sub roles of `RoleObject`.
 */
- (NSArray *)getRoles;

/**
 @abstract Returns the users contained in a role.
 @return Array of users of RoleObject.
 */
- (NSArray *)getUsers;

/**
 @abstract Checks whether current user is owner of this `RoleObject`.
 @return Returns whether or not current user is the owner of this `RoleObject`.
 */
- (BOOL)isOwner;

@end