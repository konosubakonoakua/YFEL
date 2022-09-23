#ifndef FEL_H
#define FEL_H

#include <QString>
#include <QObject>
#include <QThread>
#include <QList>
#include <QMultiMap>

#include "libusb-1.0/libusb.h"

#include "usb.h"
#include "chipworker.h"
#include "chips/chip_version.h"

class fel : QObject {
Q_OBJECT
private:
    struct fel_request_t {
        uint32_t request;
        uint32_t address;
        uint32_t length;
        uint32_t pad;
    } __attribute__((packed));

private:
    chip_version_t version{};
    usb usb_handler;

public:
    fel();

    void fel_open_usb();

    void fel_close_usb();

    void fel_scan_chip();

    [[nodiscard]] chip_version_t fel_get_chip_id() const;

private:
    void fel_chip_id();

    void send_fel_request(int type, uint32_t addr, uint32_t length);

    void read_fel_status();
};

#endif// FEL_H
