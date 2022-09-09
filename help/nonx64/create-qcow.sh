docker build -q -t compsec/qcow-builder -f qcow-builder.Dockerfile .
mkdir -p ./extract \
&& echo 'Starting Build' \
&& echo '1. Extracting files' \
&& tar -xvf $1 -C ./extract \
&& echo 'Done!'
docker run --name qcow-builder --rm -it -v "$(pwd)/:/build" compsec/qcow-builder $1
echo '3. Cleaning up files' \
&& rm -rf ./extract \
&& echo 'Done!' \
&& echo 'Finished Build'
