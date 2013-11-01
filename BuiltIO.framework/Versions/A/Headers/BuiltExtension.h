//
//  BuiltExtension.h
//  builtDemo
//
//  Created by Akshay Mhatre on 10/08/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Execute a code snippet in extension*/

@interface BuiltExtension : NSObject

/**
 @abstract Makes a call to an extension function
 @param functionName the name of the function that you want to execute
 @param requestid assign a unique id to this request. When cancelling this particular request, use this id.
 @param properties any data that you want to pass to the function
 @param successBlock on success this block will be called and `response` will contain the response from the extension method
 @param errorBlock in case of any errors this block will be called
 */
+ (void)executeWithName:(NSString *)functionName
              requestId:(NSString *)requestid
                   data:(NSDictionary *)properties
              onSuccess:(void (^)(id response))successBlock
                onError:(void (^) (NSError *error))errorBlock;

/**
 @abstract Makes a call to an extension function
 @param functionName the name of the function that you want to execute
 @param requestid assign a unique id to this request. When cancelling this particular request, use this id.
 @param successBlock on success this block will be called and `response` will contain the response from the extension method
 @param errorBlock in case of any errors this block will be called
 */
+ (void)executeWithName:(NSString *)functionName
              requestId:(NSString *)requestid
              onSuccess:(void (^)(id response))successBlock
                onError:(void (^) (NSError *error))errorBlock;

/**
 @abstract cancel a request by it's request id.
 @param requestid id of the request to cancel. This is the id which you may have set during executing the request.
 */
+ (void)cancelRequestWithId:(NSString *)requestid;

@end
