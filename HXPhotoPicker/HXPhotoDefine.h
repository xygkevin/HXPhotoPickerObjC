//
//  HXPhotoDefine.h
//  HXPhotoPickerExample
//
//  Created by Silence on 2017/11/24.
//  Copyright © 2017年 Silence. All rights reserved.
//

#ifndef HXPhotoDefine_h
#define HXPhotoDefine_h

#import <CommonCrypto/CommonDigest.h>
#import "NSBundle+HXPhotoPicker.h"
#import "HXPhotoTools.h"

/// 当前版本
#define HXVersion @"3.3.2"

// 日志输出
#ifdef DEBUG
#define NSSLog(FORMAT, ...) fprintf(stderr,"%s:%d\t%s\n",[[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String], __LINE__, [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);
#else
#define NSSLog(...)
#endif

/// 如果想要HXPhotoView的item大小自定义设置，请修改为 1
/// 如果为pod导入的话，请使用  pod 'HXPhotoPicker/CustomItem'
/// 并且实现HXPhotoView的代理
/// - (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath isAddItem:(BOOL)isAddItem photoView:(HXPhotoView *)photoView
/// 如果不实现此代理，item的小大将默认 (100, 100)
#define HXPhotoViewCustomItemSize 0

#define HXRound(x) (round(x*100000)/100000)
#define HXRoundHundreds(x) (round(x*100)/100)
#define HXRoundDecade(x) (round(x*10)/10)

#define HXRoundFrame(rect) CGRectMake(HXRound(rect.origin.x), HXRound(rect.origin.y), HXRound(rect.size.width), HXRound(rect.size.height))
#define HXRoundFrameHundreds(rect) CGRectMake(HXRoundHundreds(rect.origin.x), HXRoundHundreds(rect.origin.y), HXRoundHundreds(rect.size.width), HXRoundHundreds(rect.size.height))

#define HXEncodeKey @"HXModelArray"

#define HXCameraImageKey @"HXCameraImageURLKey"

#define HXPhotoPickerLibraryCaches [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject]

#define HXPhotoPickerDocuments [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject]

//#define HXPhotoPickerLocalModelsPath [HXPhotoPickerDocuments stringByAppendingPathComponent:[NSString stringWithFormat:@"%@/localModels", HXPhotoHeaderSearchPath]]

#define HXPhotoPickerLocalModelsPath [HXPhotoPickerLibraryCaches stringByAppendingPathComponent:@"localModels"]

#define HXPhotoHeaderSearchPath @"com.silence.hxphotopicker"

#define HXPhotoPickerAssetCachesPath [HXPhotoPickerLibraryCaches stringByAppendingPathComponent:HXPhotoHeaderSearchPath]

#define HXPhotoPickerCachesDownloadPath [HXPhotoPickerAssetCachesPath stringByAppendingPathComponent:@"download"]

#define HXPhotoPickerDownloadVideosPath [HXPhotoPickerCachesDownloadPath stringByAppendingPathComponent:@"videos"]

#define HXPhotoPickerDownloadPhotosPath [HXPhotoPickerCachesDownloadPath stringByAppendingPathComponent:@"photos"]

#define HXPhotoPickerCachesLivePhotoPath [HXPhotoPickerAssetCachesPath stringByAppendingPathComponent:@"LivePhoto"]

#define HXPhotoPickerLivePhotoVideosPath [HXPhotoPickerCachesLivePhotoPath stringByAppendingPathComponent:@"videos"]

#define HXPhotoPickerLivePhotoImagesPath [HXPhotoPickerCachesLivePhotoPath stringByAppendingPathComponent:@"images"]

#define HXShowLog NO

#define HX_UI_IS_IPAD (UIDevice.currentDevice.userInterfaceIdiom == UIUserInterfaceIdiomPad)

#define HX_ALLOW_LOCATION ([[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSLocationWhenInUseUsageDescription"] || [[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSLocationAlwaysUsageDescription"])

#define HX_PREFERS_STATUS_BAR_HIDDEN [[[NSBundle mainBundle] objectForInfoDictionaryKey:@"UIViewControllerBasedStatusBarAppearance"] boolValue]

#define HasAFNetworking (__has_include(<AFNetworking/AFNetworking.h>) || __has_include("AFNetworking.h"))

#define HasYYWebImage (__has_include(<YYWebImage/YYWebImage.h>) || __has_include("YYWebImage.h"))

#define HasYYKit (__has_include(<YYKit/YYKit.h>) || __has_include("YYKit.h"))

#define HasYYKitOrWebImage (__has_include(<YYWebImage/YYWebImage.h>) || __has_include("YYWebImage.h") || __has_include(<YYKit/YYKit.h>) || __has_include("YYKit.h"))

#define HasSDWebImage (__has_include(<SDWebImage/UIImageView+WebCache.h>) || __has_include("UIImageView+WebCache.h"))



///iPhoneX
#define HX_IS_IPhoneX_All       [HXPhotoTools isFullScreen]

#define HX_ScreenWidth          [UIScreen mainScreen].bounds.size.width
#define HX_ScreenHeight         [UIScreen mainScreen].bounds.size.height
// 导航栏 + 状态栏 的高度
#define HXStatusBarHeight       [HXPhotoTools navStatusBarHeight]
#define hxNavigationBarHeight   [HXPhotoTools navBarHeight]
#define hxTopMargin             (HX_IS_IPhoneX_All ? 44 : 0)
#define hxBottomMargin          (HX_IS_IPhoneX_All ? 34 : 0)

// 弱引用
#define HXWeakSelf __weak typeof(self) weakSelf = self;
// 强引用
#define HXStrongSelf __strong typeof(weakSelf) strongSelf = weakSelf;

#pragma mark - Hash

#define HX_MAX_FILE_EXTENSION_LENGTH (NAME_MAX - CC_MD5_DIGEST_LENGTH * 2 - 1)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
static inline NSString * _Nonnull HXDiskCacheFileNameForKey(NSString * _Nullable key, BOOL addExt) {
    const char *str = key.UTF8String;
    if (str == NULL) {
        str = "";
    }
    unsigned char r[CC_MD5_DIGEST_LENGTH];
    CC_MD5(str, (CC_LONG)strlen(str), r);
    NSURL *keyURL = [NSURL URLWithString:key];
    NSString *ext = keyURL ? keyURL.pathExtension : key.pathExtension;
    // File system has file name length limit, we need to check if ext is too long, we don't add it to the filename
    if (ext.length > HX_MAX_FILE_EXTENSION_LENGTH) {
        ext = nil;
    }
    NSString *filename = [NSString stringWithFormat:@"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                          r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9], r[10],
                          r[11], r[12], r[13], r[14], r[15]];
    if (addExt) {
        filename = [filename stringByAppendingFormat:@"%@", ext.length == 0 ? @"" : [NSString stringWithFormat:@".%@", ext]];
    }
    return filename;
}
#pragma clang diagnostic pop
CG_INLINE UIAlertController * _Nullable hx_showAlert(UIViewController * _Nullable vc,
                                          NSString * _Nullable title,
                                          NSString * _Nullable message,
                                          NSString * _Nullable buttonTitle1,
                                          NSString * _Nullable buttonTitle2,
                                          dispatch_block_t _Nullable buttonTitle1Handler,
                                          dispatch_block_t _Nullable buttonTitle2Handler) {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
                                                                             message:message
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    
    if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) {
        UIPopoverPresentationController *pop = [alertController popoverPresentationController];
        pop.permittedArrowDirections = UIPopoverArrowDirectionAny;
        pop.sourceView = vc.view;
        pop.sourceRect = vc.view.bounds;
    }
    
    if (buttonTitle1) {
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:buttonTitle1
                                                               style:UIAlertActionStyleCancel
                                                             handler:^(UIAlertAction * _Nonnull action) {
                                                                 if (buttonTitle1Handler) buttonTitle1Handler();
                                                             }];
        [alertController addAction:cancelAction];
    }
    if (buttonTitle2) {
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:buttonTitle2
                                                           style:UIAlertActionStyleDefault
                                                         handler:^(UIAlertAction * _Nonnull action) {
                                                             if (buttonTitle2Handler) buttonTitle2Handler();
                                                         }];
        [alertController addAction:okAction]; 
    }
    [vc presentViewController:alertController animated:YES completion:nil];
    return alertController;
}


#define HXAlbumCameraRoll @"HXAlbumCameraRoll"
#define HXAlbumPanoramas @"HXAlbumPanoramas"
#define HXAlbumVideos @"HXAlbumVideos"
#define HXAlbumFavorites @"HXAlbumFavorites"
#define HXAlbumTimelapses @"HXAlbumTimelapses"
#define HXAlbumRecentlyAdded @"HXAlbumRecentlyAdded"
#define HXAlbumRecents @"HXAlbumRecents"
#define HXAlbumBursts @"HXAlbumBursts"
#define HXAlbumSlomoVideos @"HXAlbumSlomoVideos"
#define HXAlbumSelfPortraits @"HXAlbumSelfPortraits"
#define HXAlbumScreenshots @"HXAlbumScreenshots"
#define HXAlbumDepthEffect @"HXAlbumDepthEffect"
#define HXAlbumLivePhotos @"HXAlbumLivePhotos"
#define HXAlbumAnimated @"HXAlbumAnimated"

#endif /* HXPhotoDefine_h */
