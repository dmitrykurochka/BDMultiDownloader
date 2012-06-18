//  BDMultiDownloader.h
//
//  Created by Norsez Orankijanan on 5/19/12.
//
//  Copyright (c) 2012, Norsez Orankijanan (Bluedot) All Rights Reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice, 
//  this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice, 
//  this list of conditions and the following disclaimer in the documentation 
//  and/or other materials provided with the distribution.
//
//  3. Neither the name of Bluedot nor the names of its contributors may be used 
//  to endorse or promote products derived from this software without specific
//  prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
//  POSSIBILITY OF SUCH DAMAGE.

#import <Foundation/Foundation.h>

/**
 * A block based singleton class that takes care of a pool of connections concurrently downloading 
 * and caching data from.
 */
@interface BDMultiDownloader : NSObject <NSURLConnectionDelegate>

/**
 * Add a path for data download. Download begins when there's a free connection 
 * available in the pool. The downloaded data is automatically cached.
 * @param urlPath path to download. 
 * @param completionWithDownloadedData block returned with downloaded data. 
 */
- (void) queueRequest:(NSString*)urlPath completion:(void(^)(NSData*))completionWithDownloadedData;

/**
 * Convenient method for downloading image files. 
 * @param urlPath path to the image
 * @param completionWithImageYesIfFromCache block returned with downloaded image, and YES if the image is returned from cache.
 */
- (void) imageWithPath:(NSString*)urlPath completion:(void(^)(UIImage*, BOOL))completionWithImageYesIfFromCache;

/**
 * Cancel all pending URL connections.
 */
- (void) clearQueue;

#pragma mark - block based delegators, they are all optional (can be nil)
//block called when encountered error
@property (nonatomic, copy) void (^onNetworkError)(NSError*);
//block called to indicates network activity. YES when there's network activity from this class. No otherwise. This can be used to toggle iOS's network status indicator.
@property (nonatomic, copy) void (^onNetworkActivity)(BOOL);
//block called to indicate progress (ranging from 0.0 to 1.0 Finished) of each request URL.
@property (nonatomic, copy) void (^onDownloadProgressWithProgressAndRequestURL)(double, NSURL*);

#pragma mark - optional configs
@property (nonatomic, assign) NSUInteger cacheSizeLimit;
@property (nonatomic, assign) NSUInteger maximumNumberOfThreads;
@property (nonatomic, strong) NSDictionary *httpHeaders;
@property (nonatomic, assign) NSTimeInterval connectionTimeout;


+ (BDMultiDownloader *)shared;
@end