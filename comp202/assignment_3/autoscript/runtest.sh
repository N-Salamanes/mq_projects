#!/bin/bash

echo 'Building...'

gcc -o dmake -g src/*.c src/*.h
if ! [ $? -eq 0 ]
then
	echo "Build Failed"
	exit 0
	
else
	echo "...Done" >&2
fi

echo '=========='



print_err()
{

	FILESIZE=$(stat -c%s "$TEST_OUTPUT/res.err")
	
	if [ "$FILESIZE" -eq "0" ];
	then
		echo "$i	FAIL		STDOUT"
	else
		diff -bB res.err expected.err > diff.err
		if [ $? -eq 0 ]
		then
			echo "$i	FAIL		STDERR+STDOUT"
		else
			LINE=$(head -n 1 $TEST_OUTPUT/res.err)
			
			if [ -z "$ERRORS" ]; then
				ERRORS="$stage	$cur_test\n		$LINE"
			else
				ERRORS="$ERRORS\n$stage	$cur_test\n		$LINE"
			fi
			
			echo "$i	FAIL		STDERR"
			
		fi
	fi
}



echo
LAB_ROOT=$PWD
OUTPUT_ROOT=$LAB_ROOT/output
TESTDATA_DIR=$LAB_ROOT/testdata
cd $TESTDATA_DIR


COUNT=0
PASSED=0
for stage in stage*
do

STAGE_OUTPUT=$OUTPUT_ROOT/$stage
STAGE_DIR=$TESTDATA_DIR/$stage

mkdir -p $STAGE_OUTPUT

cd $STAGE_DIR
echo '=========='
echo $stage
echo '=========='
	for i in {1..10}
	do
		cur_test="test$i"
		TEST_OUTPUT=$STAGE_OUTPUT/$cur_test
		TEST_DIR=$STAGE_DIR/$cur_test
		mkdir -p $TEST_OUTPUT


		#cleaning
		cd $TEST_OUTPUT
		for file in *
		do
			rm $TEST_OUTPUT/$file
		done
		
		
		cd $TEST_DIR

		#Setup test files
		for file in *
		do
			rsync -a $file $TEST_OUTPUT/.
		done
		
		#copy command
		cp ../$cur_test.cmd $TEST_OUTPUT/$cur_test.cmd
		
		#copy expected output to output folder
		cp ../$cur_test.out $TEST_OUTPUT/expected.out
		cp ../$cur_test.err $TEST_OUTPUT/expected.err
		
		
		#Run Test
		cd $TEST_OUTPUT
		
		bash $cur_test.cmd > ./res.out 2> ./res.err
		diff -bB res.out expected.out > diff.out
		if ! [ $? -eq 0 ]
		then
			print_err
		else
			diff -bB res.err expected.err > diff.err
			if [ $? -eq 0 ]
			then
				echo "$i	SUCCESS"
				PASSED=$((PASSED + 1))
			else
				print_err
			fi
		fi
		
		
		cd ..
		COUNT=$((COUNT + 1))
	done
	echo
cd ..

done

if ! [ -z "$ERRORS" ]; then
echo '=========='
echo -e $ERRORS
echo
fi

echo '=========='
if [ $PASSED == $COUNT ]
then
	echo "SUCCESS"
else
	echo 'FAILED'
fi