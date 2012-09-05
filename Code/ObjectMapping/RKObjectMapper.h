//
//  RKObjectMapper.h
//  RestKit
//
//  Created by Blake Watters on 5/6/11.
//  Copyright (c) 2009-2012 RestKit. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <CoreData/CoreData.h>
#import <Foundation/Foundation.h>
#import <RestKit/Support.h>
#import "RKObjectMapping.h"
#import "RKMappingOperation.h"
#import "RKMappingResult.h"
#import "RKMappingOperationDataSource.h"
#import "RKErrors.h"

@protocol RKObjectMapperDelegate;

@interface RKObjectMapper : NSObject

@property (nonatomic, strong, readonly) id sourceObject;
@property (nonatomic, strong, readonly) NSDictionary *mappingsDictionary;
@property (nonatomic, weak) id targetObject;
@property (nonatomic, weak) id<RKObjectMapperDelegate> delegate;
@property (weak, nonatomic, readonly) NSArray *errors;
@property (nonatomic, strong) id<RKMappingOperationDataSource> mappingOperationDataSource;

- (id)initWithObject:(id)object mappingsDictionary:(NSDictionary *)mappingsDictionary;

// Primary entry point for the mapper. Examines the type of object and processes it appropriately...
- (RKMappingResult *)performMapping:(NSError **)error;

@end

// Delegate
@protocol RKObjectMapperDelegate <NSObject>

@optional

- (void)mapperWillBeginMapping:(RKObjectMapper *)mapper;
- (void)mapperDidFinishMapping:(RKObjectMapper *)mapper;
- (void)mapper:(RKObjectMapper *)mapper didAddError:(NSError *)error;
- (void)mapper:(RKObjectMapper *)mapper didFindMappableObject:(id)object atKeyPath:(NSString *)keyPath withMapping:(RKMapping *)mapping;
- (void)mapper:(RKObjectMapper *)mapper didNotFindMappableObjectAtKeyPath:(NSString *)keyPath;

- (void)mapper:(RKObjectMapper *)mapper willMapFromObject:(id)sourceObject toObject:(id)destinationObject atKeyPath:(NSString *)keyPath usingMapping:(RKMapping *)objectMapping;
- (void)mapper:(RKObjectMapper *)mapper didMapFromObject:(id)sourceObject toObject:(id)destinationObject atKeyPath:(NSString *)keyPath usingMapping:(RKMapping *)objectMapping;
- (void)mapper:(RKObjectMapper *)mapper didFailMappingFromObject:(id)sourceObject toObject:(id)destinationObject withError:(NSError *)error atKeyPath:(NSString *)keyPath usingMapping:(RKMapping *)objectMapping;

- (void)mapper:(RKObjectMapper *)mapper willPerformMappingOperation:(RKMappingOperation *)mappingOperation; // Added in 0.11.0
@end

