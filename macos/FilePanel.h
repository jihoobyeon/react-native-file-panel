
#ifdef RCT_NEW_ARCH_ENABLED
#import "RNFilePanelSpec.h"

@interface FilePanel : NSObject <NativeFilePanelSpec>
#else
#import <React/RCTBridgeModule.h>

@interface FilePanel : NSObject <RCTBridgeModule>
#endif

@end
