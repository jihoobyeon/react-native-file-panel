#import "FilePanel.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <UniformTypeIdentifiers/UTType.h>

@implementation FilePanel
RCT_EXPORT_MODULE()

// Don't compile this code when we build for the old architecture.
#ifdef RCT_NEW_ARCH_ENABLED
- (void)openFile:(NSArray<NSString *> *)ext resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		dispatch_async(dispatch_get_main_queue(), ^{
				NSOpenPanel *panel = [NSOpenPanel openPanel];
				NSData *file = nil;
				
				[panel setCanChooseFiles:YES];
				[panel setCanChooseDirectories:NO];
				[panel setCanCreateDirectories:YES];
				[panel setAllowsMultipleSelection:NO];
				if (ext.count <= 0 || [ext[0] isEqualToString:@"*"]) {
						[panel setAllowsOtherFileTypes:YES];
				}
				else {
						NSMutableArray<UTType *> *types = [NSMutableArray arrayWithCapacity:ext.count];
						for (NSString *extension in ext) {
								UTType *type = [UTType typeWithFilenameExtension:[extension substringFromIndex:1]];
								if (type != nil) {
										[types addObject:type];
								}
						}
						[panel setAllowedContentTypes:[types copy]];
						[panel setAllowsOtherFileTypes:NO];
				}
				
				if ([panel runModal] == NSModalResponseOK) {
						file = [NSData dataWithContentsOfURL:[panel URL]];
				}
				[panel close];
				
				if (file) {
						resolve([file base64EncodedStringWithOptions:0]);
				}
				else {
						reject(@"No file selected", @"No file selected", nil);
				}
		});
}

- (void)openFiles:(NSArray<NSString *> *)ext resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		dispatch_async(dispatch_get_main_queue(), ^{
				NSOpenPanel *panel = [NSOpenPanel openPanel];
				NSArray<NSString *> *files = @[];
				
				[panel setCanChooseFiles:YES];
				[panel setCanChooseDirectories:NO];
				[panel setCanCreateDirectories:YES];
				[panel setAllowsMultipleSelection:YES];
				if (ext.count <= 0 || [ext[0] isEqualToString:@"*"]) {
						[panel setAllowsOtherFileTypes:YES];
				}
				else {
						NSMutableArray<UTType *> *types = [NSMutableArray arrayWithCapacity:ext.count];
						for (NSString *extension in ext) {
								UTType *type = [UTType typeWithFilenameExtension:[extension substringFromIndex:1]];
								if (type != nil) {
										[types addObject:type];
								}
						}
						[panel setAllowedContentTypes:[types copy]];
						[panel setAllowsOtherFileTypes:NO];
				}
				
				if ([panel runModal] == NSModalResponseOK) {
						NSMutableArray<NSString *> *temp = [NSMutableArray arrayWithCapacity:[[panel URLs] count]];
						for (NSURL *file in [panel URLs]) {
								[temp addObject:[[NSData dataWithContentsOfURL:file] base64EncodedStringWithOptions:0]];
						}
						files = [temp copy];
				}
				[panel close];
				
				if (files.count > 0) {
						resolve(files);
				}
				else {
						reject(@"No file selected", @"No file selected", nil);
				}
		});
}


- (void)openFolder:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		dispatch_async(dispatch_get_main_queue(), ^{
				NSOpenPanel *panel = [NSOpenPanel openPanel];
				NSURL *folder = nil;
				
				[panel setCanChooseFiles:NO];
				[panel setCanChooseDirectories:YES];
				[panel setCanCreateDirectories:YES];
				[panel setAllowsOtherFileTypes:NO];
				
				if ([panel runModal] == NSModalResponseOK) {
						folder = [panel URL];
				}
				[panel close];
				
				if (folder) {
						resolve([folder absoluteString]);
				}
				else {
						reject(@"No folder selected", @"No folder selected", nil);
				}
		});
}

- (void)saveFile:(NSArray<NSString *> *)ext content:(NSString *)content resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject {
		dispatch_async(dispatch_get_main_queue(), ^{
				NSSavePanel *panel = [NSSavePanel savePanel];
				
				[panel setCanCreateDirectories:YES];
				if (ext.count <= 0 || [ext[0] isEqualToString:@"*"]) {
						[panel setAllowsOtherFileTypes:YES];
				}
				else {
						NSMutableArray<UTType *> *types = [NSMutableArray arrayWithCapacity:ext.count];
						for (NSString *extension in ext) {
								UTType *type = [UTType typeWithFilenameExtension:[extension substringFromIndex:1]];
								if (type != nil) {
										[types addObject:type];
								}
						}
						[panel setAllowedContentTypes:[types copy]];
						[panel setAllowsOtherFileTypes:NO];
				}
				
				if ([panel runModal] == NSModalResponseOK) {
						[[[NSData alloc] initWithBase64EncodedString:content options:0] writeToFile:[[panel URL] path] atomically:YES];
				}
				[panel close];
			
				resolve(nil);
		});
}

- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params
{
    return std::make_shared<facebook::react::NativeFilePanelSpecJSI>(params);
}
#endif

@end

