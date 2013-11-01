//
//  BuiltFile.h
//  builtDemo
//
//  Created by Akshay Mhatre on 26/02/13.
//  Copyright (c) 2013 raweng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FileObject.h"

@protocol FileUploadDelegate <NSObject>

-(void)fileUploadSuccess;
-(void)fileUploadError;

@end

/**BuiltFile class to upload multiple images and files to built.io*/
@interface BuiltFile : NSObject{
    __weak id <FileUploadDelegate> fileUploadDelegate;
}

/**
 @abstract Gives total count of the objects if includeCount method is called.
 */
@property (nonatomic, assign) NSInteger totalCount;


/**--------------------------------------------------------------------------------------
 @name Add file objects for uploading
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract Add `FileObject`s to be uploaded
 @discussion Enqueue files/images to be uploaded
 @param file An object of FileObject
 @param key add the file(s) against key(s). After uploading the files, the `FileObject`s will be returned against these keys.
 */
- (void)addFile:(FileObject *)file forKey:(NSString *)key;


/**---------------------------------------------------------------------------------------
 * @name Save files with built.io
 *  ---------------------------------------------------------------------------------------
 */

/**
 @abstract Upload one or more images/files to built.io
 @param successBlock this block returns a dictionary with the keys that were passed in the addFile:forKey: method and values as `FileObject`s
 @param errorBlock callBack in case of failure
 */
- (void)saveOnSuccess:(void (^)(NSDictionary *fileUploadDictionary))successBlock
              onError:(void (^)(NSError *error))errorBlock;


@property (nonatomic,weak) id <FileUploadDelegate> fileUploadDelegate;


/**---------------------------------------------------------------------------------------
 * @name Creating a BuiltFile Object
 *  ---------------------------------------------------------------------------------------
 */

/**
    @abstract BuiltFile class to upload multiple images and files in built.io
    @return Returns BuiltFile object.
 */
+ (BuiltFile *)file;

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
    @param key Key for which to remove the header value
 */
- (void)removeHeaderForKey:(NSString *)key;


/** --------------------------------------------------------------------------------------
 @name Set api key and app uid for another application
 -----------------------------------------------------------------------------------------
 */

/**
 @abstract If you require to upload file/fetch file details belonging to some other application, you can use this method to set the app parameters
 @param apiKey api key of the app
 @param uid appuid of the app
 */
- (void)setApplicationApiKey:(NSString *)apiKey andUid:(NSString *)uid;


/** --------------------------------------------------------------------------------------
 @name Fetch uploads
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract fetch all the uploads
 @param successBlock an array of `FileObject`s
 @param errorBlock callBack in case of failure
 */
- (void)fetchAllOnSuccess:(void (^)(NSArray *allFiles))successBlock
                   onError:(void (^)(NSError *error))errorBlock;

/**
 @abstract fetch all the images
 @param successBlock an array of `FileObject`s
 @param errorBlock callBack in case of failure
 */
- (void) fetchImagesOnSuccess:(void (^)(NSArray *allImages))successBlock
                      onError:(void (^)(NSError *error))errorBlock;

/**
 @abstract fetch all the videos
 @param successBlock an array of `FileObject`s
 @param errorBlock callBack in case of failure
 */
- (void) fetchVideosOnSuccess:(void (^)(NSArray *allVideos))successBlock
                      onError:(void (^)(NSError *error))errorBlock;


/**--------------------------------------------------------------------------------------
 @name Paginating results
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract The number of objects to skip before returning any.
 @discussion The skip parameter can be used for pagination. "skip" specifies the number of objects to skip in the response.
 @param number No of objects to skip from returned objects.
 */
- (void)skipObjects:(NSNumber *)number;

/**
 @abstract A limit on the number of objects to return.
 @discussion The limit parameter can be used for pagination. "limit" specifies the number of objects to limit to in the response.
 @param number No of objects to limit.
 */
- (void)limitObjects:(NSNumber *)number;


/**--------------------------------------------------------------------------------------
 @name Include total count of objects
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract Gives total object count alongwith objects returned in response. Access totalCount property to get the count.
 */
- (void)includeCount;

/**
 @abstract Gives total object count only. No uploads are returned. Access totalCount property to get the count.
 */
- (void)count;

/** --------------------------------------------------------------------------------------
 @name Cancel
 -----------------------------------------------------------------------------------------
 */
/**
 @abstract cancel ongoing file uploading network requests
 */
- (void)cancel;

@end
