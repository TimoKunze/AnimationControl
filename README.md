<p align=center>
  <a href="https://github.com/TimoKunze/AnimationControl/releases">
    <img alt="Download AnimationControl" src="https://img.shields.io/badge/download-latest-0688CB.svg">
  </a>
  <a href="https://github.com/TimoKunze/AnimationControl/blob/master/LICENSE">
    <img alt="License" src="https://img.shields.io/badge/license-MIT-0688CB.svg">
  </a>
  <a href="https://www.paypal.com/xclick/business=TKunze71216%40gmx.de&item_name=AnimationControl&no_shipping=1&tax=0&currency_code=EUR">
    <img alt="Donate" src="https://img.shields.io/badge/%24-donate-E44E4A.svg">
  </a>
</p>

# AnimationControl
An ActiveX control for Visual Basic 6 that can be used to display AVI or GIF animations.

I've developed this ActiveX control in 2006 and did update it on a regular basis until 2016. Currently I have little interest to maintain this project any longer, but I think the code might be of some use to others.

# Before you make changes
If you make changes to the code and deploy the binary, keep in mind that ActiveX controls are COM components and therefore should stay binary compatible as long as you don't change the COM object's, i.e. the ActiveX control's public class name and GUIDs. Otherwise people using these components are likely to end up in the famous COM hell.