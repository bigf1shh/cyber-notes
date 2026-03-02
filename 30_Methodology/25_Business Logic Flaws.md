# Examples

## 1. Excessive trust in client-side controls

- Change integer values into alphanumeric
- Escape from common flow to bypass login2

## 2. Failing to handle unconventional input

- Turn values into negative
- Turn small int into big int
- Try super big "email" to bypass verification `aaaaaaaaaaaaaaaaaaaaaaaaaa@dontwannacry.com.your-email.com`

## 3. Making flawed assumptions about user behavior

- Remove one parameter at a time to ensuer all relevant code paths are reached
- Try deleting the name of the parameter as well as the value.
- Follow multi-stage process through to completino. Sometimes tampering with parameter in one step will have an effect on another stop further along in the workflow.
	- Don't forget to check cookies too.
- Change the expected flow