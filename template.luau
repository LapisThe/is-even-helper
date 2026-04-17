-- ModuleScript

local Module = {}

function Module.IsEven(PassedNumber)
	if type(PassedNumber) ~= "number" then
		error("Passed number not a number.")
		return nil
	end

	if PassedNumber < [1] or PassedNumber > [2] then
		print("Number not supported")
	end

	[3]

	return nil
end

return Module
