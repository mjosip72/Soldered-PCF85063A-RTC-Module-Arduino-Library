# Real time clock RTC PCF85063A breakout Arduino library

[![Make docs and publish to GitHub Pages](https://github.com/e-radionicacom/Soldered-Generic-Arduino-Library/actions/workflows/make_docs.yml/badge.svg?branch=dev)](https://github.com/e-radionicacom/Soldered-Generic-Arduino-Library/actions/workflows/make_docs.yml)

| ![Real time clock RTC PCF85063A breakout](https://upload.wikimedia.org/wikipedia/commons/8/8f/Example_image.svg) |
| :---------------------------------------------------------------------------------------------: |
| [Real time clock RTC PCF85063A breakout](https://www.solde.red/333051)                                                            |

RTC (Real Time Clock) is a device that carefully and precisely tracks time and dates. It is extremely precise so as a long-term solution, it is better for time tracking than clock on microcontrollers. This breakout can work with extremely low current and thanks to the alarm option and interrupt pin, it will allow a microcontroller to enter sleep mode until its awaken by this RTC.

It has a built-in battery holder (doesn't come with a battery) and even if power is lost, real-time won't be affected.

- Communication:  I2C
- RTC IC: PCF85063A
- Voltage: 0.9V - 5.5V
- easyC connector
- Dimensions: 36 x 22 mm (https://www.soldered.com/en/easyC)

### Repository Contents
- **/src** - source files for the library (.h & .cpp)
- **/examples** - examples for using the library
- ***other*** - *keywords* file highlights function words in your IDE, *library.properties* enables implementation with Arduino Library Manager.

### Hardware design
You can find hardware design for this board in [*Real time clock RTC PCF85063A breakout*](https://github.com/SolderedElectronics/NAZIVPROIZVODA-hardware-design) hardware repository.

### Documentation

Access Arduino library documentation [here](https://SolderedElectronics.github.io/Soldered-Generic-Arduino-Library/).

- Tutorial for using the NAZIV PROIZVODA board
- Installing an Arduino library

### Board compatibility

The library is compatible with board & microcontroller families shown in green below: 

[![Compile Sketches](http://github-actions.40ants.com/e-radionicacom/Soldered-Generic-Arduino-Library/matrix.svg?branch=dev&only=Compile%20Sketches)](https://github.com/e-radionicacom/Soldered-Generic-Arduino-Library/actions/workflows/compile_test.yml)


### About Soldered
<img src="https://raw.githubusercontent.com/e-radionicacom/Soldered-Generic-Arduino-Library/dev/extras/Soldered-logo-color.png" alt="soldered-logo" width="500"/>

At Soldered, we design and manufacture a wide selection of electronic products to help you turn your ideas into acts and bring you one step closer to your final project. Our products are intented for makers and crafted in-house by our experienced team in Osijek, Croatia. We believe that sharing is a crucial element for improvement and innovation, and we work hard to stay connected with all our makers regardless of their skill or experience level. Therefore, all our products are open-source. Finally, we always have your back. If you face any problem concerning either your shopping experience or your electronics project, our team will help you deal with it, offering efficient customer service and cost-free technical support anytime. Some of those might be useful for you:

- [Web Store](https://www.soldered.com/shop)
- [Tutorials & Projects](https://soldered.com/learn)
- [Community & Technical support](https://soldered.com/community)


### Original source
​
This library is possible thanks to original [arduino-mcp23017](https://github.com/blemasle/arduino-mcp23017) library. Thank you, blemasle. 


### Open-source license
Soldered invests vast amounts of time into hardware & software for these products, which are all open-source. Please support future development by buying one of our products. 

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all designs in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, Soldered (TAVU) will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository. 

## Have fun! 
And thank you from your fellow makers at Soldered Electronics.