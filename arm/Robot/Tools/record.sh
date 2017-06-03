rm -rf record.tar.gz
rm -rf record
mkdir record

tar -zcvf frontImages.tar.gz frontImages
tar -zcvf topImages.tar.gz topImages
tar -zcvf MapSnapShoots.tar.gz MapSnapShoots/*ocp*
tar -zcvf logs.tar.gz logs

mv frontImages.tar.gz record
mv topImages.tar.gz record
mv MapSnapShoots.tar.gz record
mv logs.tar.gz record
mv *.log record
mv *.jpg record

tar -zcf record.tar.gz record

rm -rf frontImages/*
rm -rf topImages/*
rm -rf MapSnapShoots/*
rm -rf logs/*
