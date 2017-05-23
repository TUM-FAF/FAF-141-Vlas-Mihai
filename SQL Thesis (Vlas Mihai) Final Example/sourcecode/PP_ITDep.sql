Create view vwITEmployees
as
SELECT Id, Name, Salary, Gender, DeptName
from tblEmployee
join tblDepartment
on tblEmployee.DepartmentId=tblDepartment.DeptId
where tblDepartment.DeptName='IT'

GO
Select * from vwITEmployees

