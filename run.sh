

while getopts cdhmrt OPT
do
    case "$OPT" in
    c) clear;;
    d) rm -rf bin/ build/;;
   h)  echo
            echo "         -c: clear the screen"
            echo "         -d: delete the bin and build folder"
            echo "         -h: list all commands"
            echo "         -m: compile the program"
            echo "         -r: run the program"
            echo "         -t: run the test_script"
            echo ;;
    m) make;;
    r) rm output.ppm
    ./bin/convert flood  1 0 0 0 0 > output.ppm < img.ppm;;
    t) python3.10  test/run_tests.py;;
    esac
done