using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace StudGroupApp
{
    public class Student
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public DateTime DateOfBirth { get; set; }
        public string Group { get; set; }
        public List<int> Grades { get; set; }
        public int Absences { get; set; }

        public double AverageGrade => Grades.Any() ? Grades.Average() : 0;
    }

    public class StudGroup
    {
        public List<Student> Students { get; set; } = new List<Student>();

        public void AddStudent(Student student)
        {
            Students.Add(student);
        }

        public void SaveToFile(string filePath)
        {
            using (var writer = new StreamWriter(filePath))
            {
                foreach (var student in Students)
                {
                    writer.WriteLine($"{student.FirstName},{student.LastName},{student.DateOfBirth},{student.Group},{string.Join(";", student.Grades)},{student.Absences},{student.AverageGrade}");
                }
            }
        }

        public void LoadFromFile(string filePath)
        {
            using (var reader = new StreamReader(filePath))
            {
                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    var parts = line.Split(',');
                    var student = new Student
                    {
                        FirstName = parts[0],
                        LastName = parts[1],
                        DateOfBirth = DateTime.Parse(parts[2]),
                        Group = parts[3],
                        Grades = parts[4].Split(';').Select(int.Parse).ToList(),
                        Absences = int.Parse(parts[5])
                    };
                    Students.Add(student);
                }
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var studGroup = new StudGroup();

            studGroup.AddStudent(new Student
            {
                FirstName = "Alex",
                LastName = "Alender",
                DateOfBirth = new DateTime(2007, 4, 20),
                Group = "AT24I",
                Grades = new List<int> { 2, 5, 3 },
                Absences = 2
            });

            studGroup.SaveToFile(@"Path");

            var loadedGroup = new StudGroup();
            loadedGroup.LoadFromFile(@"Path");

            foreach (var student in loadedGroup.Students)
            {
                Console.WriteLine($"{student.FirstName} {student.LastName} - GPA (Grade Point Average): {student.AverageGrade}");
            }
        }
    }
}
