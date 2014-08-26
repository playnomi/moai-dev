//
//  CBMoreAppsButton.h
//  Chartboost
//  VERSION
//
//  Copyright 2011 Chartboost. All rights reserved.
//

#import <UIKit/UIKit.h>
@class CBBadgeView;
@interface CBMoreAppsButton : UIView

/*!
@abstract returns a button with a custom image that is launches the More Applications page.

@param customImage the UIImage object to be displayed as the button interface.
 
@param viewController the view controller object to which the button with be added.
 
@param location The location for the Chartboost impression type.

@return CBMoreAppsButton formatted with a custom image and badge icon.
 
@discussion This method returns a customizable button with update badge that launches the more apps
page from an optional presenting view controller object or the main window if nil. The frame of the
button is set to the size of the customImage object plus the radius of the badge icon. The position 
of this object can be adjusted using the center property of the button object after initialization.
 
*/

+ (CBMoreAppsButton *)moreAppsButtonWithImage:(UIImage *)customImage
                           fromViewController:(UIViewController *)viewController
                                     location:(CBLocation)location;

@end
