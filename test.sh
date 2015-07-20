python test/auto_test/test.py $@
mkdir test/build
cd test/build
cmake ..
make
for file in "$@"
do
    ./${file}_test
done
cd ../..
