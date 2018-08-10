
"""Setup script for CWLite/1200 with XMEGA (CW303/CW308-XMEGA/CWLite target)
Configures scope settings to prepare for capturing power traces in purpose of breaking RSA
"""

# GUI compatibility
try:
    scope = self.scope
except NameError:
    pass

target.key_cmd = ""
target.output_cmd = ""
scope.clock.adc_src = "clkgen_x1"
scope.adc.samples = 24000