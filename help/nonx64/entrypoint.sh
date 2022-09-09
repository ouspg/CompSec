echo '2. Building image, this will take a (long) while...' \
&& qemu-img convert -c -O qcow2 "$(echo extract/*.vmdk)" "$1.qcow2" \
&& echo 'Done!'