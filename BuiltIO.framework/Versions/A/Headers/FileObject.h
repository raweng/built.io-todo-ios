//
//  FileObject.h
//  builtDemo
//
//  Created by Akshay Mhatre on 01/07/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BuiltACL.h"

/**Use FileObject Class to upload a single file to built.io*/
@interface FileObject : NSObject

/**----------------------------------------------------------------------------------------
 * @name Properties
 *-----------------------------------------------------------------------------------------
 */
/**
 @abstract the filename of the uploaded file
 */
@property (nonatomic, strong) NSString *filename;

/**
 @abstract the filesize of the uploaded file
 */
@property (nonatomic, assign) unsigned int filesize;

/**
 @abstract the contentType of the uploaded file
 */
@property (nonatomic, strong) NSString *contentType;

/**
 @abstract the uid of the uploaded file
 */
@property (nonatomic, strong) NSString *uid;

/**
 @abstract the tags associated with the uploaded file
 */
@property (nonatomic, strong) NSArray *tags;

/**
 @abstract the ACL applied to the uploaded file
 */
@property (nonatomic, strong) BuiltACL *ACL;

/**
 @abstract the url of the uploaded file
 */
@property (nonatomic, strong) NSString *url;


/**---------------------------------------------------------------------------------------
 * @name Creating a FileObject object
 *  ---------------------------------------------------------------------------------------
 */
/**
 @abstract FileObject class to upload single image/file to built.io
 @return Returns FileObject object.
 */
+ (FileObject *)fileObject;


/**----------------------------------------------------------------------------------------
 * @name Attaching/Removing Headers
 *-----------------------------------------------------------------------------------------
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


/**--------------------------------------------------------------------------------------
 @name Add file/data/image for uploading
 -----------------------------------------------------------------------------------------
 */

/**
 @abstract Add file to be uploaded
 @param filePath path of the file from NSBundle
 @param key add file against a key.
 */
- (void)setFile:(NSString *)filePath forKey:(NSString *)key;


/**
 @abstract Add data to be uploaded
 @param data `NSData` representation of any object to be uploaded
 @param key add data against a key.
 */
- (void)setData:(NSData *)data forKey:(NSString *)key;


/**
 @abstract Add image to be uploaded
 @param image `UIImage` object to be uploaded
 @param key add image against a key.
 */
- (void)setImage:(UIImage *)image forKey:(NSString *)key;


/** --------------------------------------------------------------------------------------
 @name Save file to built.io
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract save files to built.io
 @param successBlock callback when the file is successfully uploaded.
 @param errorBlock CallBack in case of failure.
 */
- (void)saveOnSuccess:(void (^) (void))successBlock
              onError:(void (^)(NSError *error))errorBlock;


/**--------------------------------------------------------------------------------------
 @name Fetch a file object
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract Fetches a file object when provided UID.
 @param successBlock CallBack in case of success.
 @param errorBlock CallBack in case of failure.
 */
- (void)fetchonSuccess:(void (^) (void))successBlock
               onError:(void (^)(NSError *error))errorBlock;


/**--------------------------------------------------------------------------------------
 @name Delete a file object
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract Deletes the FileObject with specified UID.
 @discussion Deletes the BuiltObject with specified object UID.
 @param successBlock CallBack in case of success.
 @param errorBlock CallBack in case of failure.
 */
- (void)destroyOnSuccess:(void (^) (void))successBlock
                 onError:(void (^) (NSError *error))errorBlock;

/**--------------------------------------------------------------------------------------
 @name Cancel
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract cancel ongoing file uploading network requests
 */
- (void)cancel;

@end
