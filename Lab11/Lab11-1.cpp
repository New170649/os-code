#include <iostream>
#include <bitset>
#include <thread>
#include <chrono>
#include <queue>
#include <functional>
#include <mutex>
#include <string>

using namespace std;

// TODO 1: สร้าง struct สำหรับ Status Register
struct StatusRegister {
    bool busy = false;
    bool error = false;
    bool ready = true;
    bool transferComplete = false;
};

// TODO 2: สร้าง class IOPort
class IOPort {
public:
    uint8_t dataRegister;
    StatusRegister status;
    uint8_t controlRegister;

    IOPort() : dataRegister(0), controlRegister(0) {
        // Initialize registers
    }

    // TODO 3: เขียน method writeData
    void writeData(uint8_t data) {
        if (status.busy) {
            cout << "[PORT ERROR] Device is busy!" << endl;
            return;
        }
        status.busy = true;
        status.ready = false;
        dataRegister = data;
        
        // จำลองเวลาประมวลผล
        this_thread::sleep_for(chrono::milliseconds(100));
        
        status.busy = false;
        status.ready = true;
        status.transferComplete = true;
    }

    // TODO 4: เขียน method readData()
    uint8_t readData() {
        return dataRegister;
    }

    // TODO 5: เขียน method pollStatus()
    bool pollStatus() {
        return status.ready;
    }
};

// TODO 6: สร้าง class DeviceController
class DeviceController {
private:
    IOPort port;
    string deviceName;
    queue<function<void()>> interruptQueue;

public:
    DeviceController(string name) : deviceName(name) {}

    // TODO 7: จำลอง Polling I/O
    void pollingIO(uint8_t data) {
        cout << "[POLLING] Waiting for device " << deviceName << " ready..." << endl;
        while (!port.pollStatus()) {
            // วน loop จนกว่า device จะพร้อม (Busy Waiting)
        }
        port.writeData(data);
        cout << "[POLLING] Data " << (int)data << " written to " << deviceName << endl;
    }

    // TODO 8: จำลอง Interrupt-driven I/O
    void interruptDrivenIO(uint8_t data, function<void()> callback) {
        cout << "[INTERRUPT] Sending data, registering interrupt handler..." << endl;
        
        // จำลองการทำงานแบบ Background
        interruptQueue.push([this, data, callback]() {
            this->port.writeData(data);
            callback(); // เรียกเมื่อโอนข้อมูลเสร็จ
        });
    }

    void processInterrupts() {
        while (!interruptQueue.empty()) {
            auto handler = interruptQueue.front();
            handler();
            interruptQueue.pop();
        }
    }
};

int main() {
    cout << "--- I/O Hardware Simulation ---" << endl;
    DeviceController keyboard("Keyboard");
    DeviceController disk("Disk Drive");

    // TODO 9: ทดสอบ Polling I/O
    cout << "\n--- Polling I/O Test ---" << endl;
    keyboard.pollingIO(65); // ส่งรหัส 'A'

    // TODO 10: ทดสอบ Interrupt-driven I/O
    cout << "\n--- Interrupt-driven I/O Test ---" << endl;
    disk.interruptDrivenIO(100, []() {
        cout << "[CALLBACK] Disk transfer complete! Interrupt handled." << endl;
    });
    
    // ประมวลผลคิวของ Interrupt
    disk.processInterrupts();

    return 0;
}