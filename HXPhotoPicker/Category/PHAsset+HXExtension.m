//
//  PHAsset+HXExtension.m
//  HXPhotoPickerExample
//
//  Created by Slience on 2021/6/8.
//  Copyright © 2021 洪欣. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PHAsset+HXExtension.h"
#import "HXPhotoDefine.h"

@implementation PHAsset (HXExtension)

- (void)hx_checkForModificationsWithAssetPathMethodCompletion:(void (^)(BOOL))completion {
    [self requestContentEditingInputWithOptions:nil completionHandler:^(PHContentEditingInput *contentEditingInput, NSDictionary *info) {
        AVAsset *avAsset = contentEditingInput.audiovisualAsset;
        NSString *path = avAsset ? [avAsset description] : contentEditingInput.fullSizeImageURL.path;
        completion([path containsString:@"/Mutations/"]);
    }];
}
@end
