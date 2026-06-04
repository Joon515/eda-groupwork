import pyuvm  # pyright: ignore[reportMissingImports]


class FifoWriteDriver(pyuvm.uvm_driver):
    pass


class FifoReadDriver(pyuvm.uvm_driver):
    pass


class FifoMonitor(pyuvm.uvm_component):
    pass


class FifoEnv(pyuvm.uvm_env):
    def build_phase(self):
        super().build_phase()
        self.write_driver = FifoWriteDriver("write_driver", self)
        self.read_driver = FifoReadDriver("read_driver", self)
        self.monitor = FifoMonitor("monitor", self)
