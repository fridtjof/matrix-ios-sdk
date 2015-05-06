/*
 Copyright 2015 OpenMarket Ltd

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <UIKit/UIKit.h>

/**
 The `MXCallStack` is an abstract interface to integrate a VoIP call stack.
 
 @discussion
 `MXCallManager` manages Matrix call events for signalling call but
 `MXCallManager` uses it to connect peer to peer streams.
 
 Limitation: 
  - it is limited to one to one call.
  - the current interface manages only one call at a time.
 */
@protocol MXCallStack <NSObject>

/**
 Start capturing device media.
 
 @param video YES if video must be captured. In YES, `selfVideoView` and `remoteVideoView` must be
        provided.
 @param success A block object called when the operation succeeds.
 @param failure A block object called when the operation fails.
 */
- (void)startCapturingMediaWithVideo:(BOOL)video
                             success:(void (^)())success
                             failure:(void (^)(NSError *error))failure;

/**
 Terminate the current call.
 */
- (void)terminate;


#pragma mark - Incoming call
/**
 Handle a incoming offer from a peer.

 This offer came within a m.call.invite event sent by the peer. 
 The implementation must return a sdp description `MXCallManager` will
 send back in a m.call.answer event.

 @param sdpOffer the description of the peer media.
 @param success A block object called when the operation succeeds. It provides a description
                of the answer.
 @param failure A block object called when the operation fails.
 */
- (void)handleOffer:(NSString*)sdpOffer
            success:(void (^)(NSString *sdpAnswer))success
            failure:(void (^)(NSError *error))failure;


#pragma mark - Outgoing call
/**
 Create an offer.

 The created sdp will be sent to the Matrix room in a m.call.invite event.

 @param success A block object called when the operation succeeds. It provides a description 
                of the offer.
 @param failure A block object called when the operation fails.
 */
- (void)createOffer:(void (^)(NSString *sdp))success
            failure:(void (^)(NSError *error))failure;

/**
 Handle a answer from the peer.
 
 This answer came within a m.call.answer event sent by the peer.

 @param sdp the description of the peer media.
 @param success A block object called when the operation succeeds. 
 @param failure A block object called when the operation fails.
 */
- (void)handleAnswer:(NSString*)sdp
             success:(void (^)())success
             failure:(void (^)(NSError *error))failure;

/**
 The UIView that receives frames from the user's camera.
 */
@property (nonatomic) UIView *selfVideoView;

/**
 The UIView that receives frames from the remote camera.
 */
@property (nonatomic) UIView *remoteVideoView;

@end