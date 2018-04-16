## gen-test.py
call with:
python gen-test.py `<max-people>` `<num-test-cases>` `<prob-occupied>`

or no parameters wich is equivalent to:

python gen-test.py 30, 5, 0.5

  * `<max-people>` - number of peoply  is random within [1,max-people]
  * `<num-test-cases>`
  * `<prob-occupied>` - for each cell we roll whether it is occupied. roll is successfull with this prob, i.e. prob-occupied has to be from [0,1]
