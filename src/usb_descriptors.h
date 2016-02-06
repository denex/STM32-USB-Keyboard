const struct usb_device_descriptor dev = {
        .bLength = USB_DT_DEVICE_SIZE,
        .bDescriptorType = USB_DT_DEVICE,
        .bcdUSB = 0x0200,
        .bDeviceClass = 0,
        .bDeviceSubClass = 0,
        .bDeviceProtocol = 0,
        .bMaxPacketSize0 = 64,
        .idVendor = VENDOR_ID,
        .idProduct = PRODUCT_ID,
        .bcdDevice = 0x0200,
        .iManufacturer = 1,
        .iProduct = 2,
        .iSerialNumber = 3,
        .bNumConfigurations = 1,
};

static const uint8_t hid_report_descriptor[] = {
  0x05, 0x01,      	// USAGE_PAGE (Generic Desktop)
  0x09, 0x06,      	// USAGE (Keyboard)
  0xA1, 0x01,      	// COLLECTION (Application)
  0x05, 0x07,      	//   USAGE_PAGE (Keyboard)
  0x19, 0xE0,      	//   USAGE_MINIMUM (Keyboard LeftControl)
  0x29, 0xE7,      	//   USAGE_MAXIMUM (Keyboard Right GUI)
  0x15, 0x00,      	//   LOGICAL_MINIMUM (0)
  0x25, 0x01,      	//   LOGICAL_MAXIMUM (1)
  0x75, 0x01,      	//   REPORT_SIZE (1)
  0x95, 0x08,      	//   REPORT_COUNT (8)
  0x81, 0x02,      	//   INPUT (Data,Var,Abs)
  0x95, 0x01,      	//   REPORT_COUNT (1)
  0x75, 0x08,      	//   REPORT_SIZE (8)
  0x81, 0x01,      	//   INPUT (Cnst,Ary,Abs)
  0x95, 0x03,      	//   REPORT_COUNT (3)
  0x75, 0x01,      	//   REPORT_SIZE (1)
  0x05, 0x08,      	//   USAGE_PAGE (LEDs)
  0x19, 0x01,      	//   USAGE_MINIMUM (Num Lock)
  0x29, 0x03,      	//   USAGE_MAXIMUM (Scroll Lock)
  0x91, 0x02,      	//   OUTPUT(Data,Var,Abs)
  0x95, 0x05,      	//   REPORT_COUNT (5)
  0x75, 0x01,      	//   REPORT_SIZE (1)
  0x91, 0x01,      	//   OUTPUT(Const,Ary,Abs)
  0x95, 0x06,      	//   REPORT_COUNT (6)
  0x75, 0x08,      	//   REPORT_SIZE (8)
  0x15, 0x00,      	//   LOGICAL_MINIMUM (0)
  0x26, 0xFF, 0x00,	//   LOGICAL_MAXIMUM (255)
  0x05, 0x07,      	//   USAGE_PAGE (Keyboard)
  0x19, 0x00,      	//   USAGE_MINIMUM (0)
  0x2A, 0xFF, 0x00,	//   USAGE_MAXIMUM (255)
  0x81, 0x00,      	//   INPUT (Data,Ary,Abs)
  0xC0
};

static const uint8_t USBD_HID_Desc[] = {
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  0x21, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  65,/*wItemLength: Total length of Report descriptor*/
  0x00,
};

static const struct {
	struct usb_hid_descriptor hid_descriptor;
	struct {
		uint8_t bReportDescriptorType;
		uint16_t wDescriptorLength;
	} __attribute__((packed)) hid_report;
} __attribute__((packed)) hid_function = {
	.hid_descriptor = {
		.bLength = sizeof(hid_function),
		.bDescriptorType = USB_DT_HID,
		.bcdHID = 0x0100,
		.bCountryCode = 0,
		.bNumDescriptors = 1,
	},
	.hid_report = {
		.bReportDescriptorType = USB_DT_REPORT,
		.wDescriptorLength = sizeof(hid_report_descriptor),
	},
};

const struct usb_endpoint_descriptor hid_endpoint = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x81,
	.bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
	.wMaxPacketSize = 64,
	.bInterval = 0x20,
};

const struct usb_interface_descriptor hid_iface = {
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = USB_CLASS_HID,
	.bInterfaceSubClass = 1, /* boot */
	.bInterfaceProtocol = 1, /* keyboard */
	.iInterface = 0,

	.endpoint = &hid_endpoint,

	.extra = &hid_function,
	.extralen = sizeof(hid_function),
};

const struct usb_interface ifaces[] = {{
	.num_altsetting = 1,
	.altsetting = &hid_iface,
}};

const struct usb_config_descriptor config = {
	.bLength = USB_DT_CONFIGURATION_SIZE,
	.bDescriptorType = USB_DT_CONFIGURATION,
	.wTotalLength = 0,
	.bNumInterfaces = 1,
	.bConfigurationValue = 1,
	.iConfiguration = 0,
	.bmAttributes = 0b11000000,
	.bMaxPower = 0x32,

	.interface = ifaces,
};

static const char *usb_strings[] = {
	"Lukas macht USB",
	"Alles Kaputt",
	"Fake Keyboard",
};
