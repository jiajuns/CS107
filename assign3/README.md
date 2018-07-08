# Assign3

## Unix filters
    sort samples/names | uniq -D | uniq -c | sort | tail -n 3

Is a pipeline that print out the most three common name in the `names` list


