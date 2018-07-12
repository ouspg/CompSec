"""Setup script for CWLite/1200 with XMEGA (CW303/CW308-XMEGA/CWLite target)

Configures scope settings to prepare for capturing SimpleSerial power traces
"""

# GUI compatibility
try:
    scope = self.scope
except NameError:
    pass
    
scope.gain.gain = 40
scope.adc.samples = 1000
scope.adc.offset = 0
scope.adc.basic_mode = "rising_edge"
scope.clock.clkgen_freq = 7370000
scope.clock.adc_src = "clkgen_x4"
scope.trigger.triggers = "tio4"
scope.io.tio1 = "serial_rx"
scope.io.tio2 = "serial_tx"
scope.io.hs2 = "clkgen"

target.protver = 1.0
target.read_timeout = 100
target.key_cmd =''
target.go_cmd = 'test\n'
target.output_cmd= '$GLITCH$'

scope.glitch.trigger_src = 'ext_single'
scope.adc.basic_mode = 'rising_edge'


scope.glitch.clk_src     = 'clkgen'
scope.io.hs2 = 'glitch'

scope.glitch.offset = 0
scope.glitch.width = 1
scope.glitch.repeat = 3

