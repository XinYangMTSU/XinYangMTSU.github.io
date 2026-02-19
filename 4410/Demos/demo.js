//constructor function

function Person(name, age){
	this.name = name;
	this.age = age;
}

Person.prototype.greet = function(){
	return "Hello, my name is " + this.name;
}

let person1 = new Person("Alice", 18);
let person2 = new Person("Bob", 25);

console.log(person1.greet());
console.log(person2.greet());

console.log(person1.name + " " + person1.age);
console.log(person2.name + " " + person2.age);


let person = {
	firstName: "John",
	lastName: "Doe",
	age: 30,
	isStudent: false,
	
	getPersonInfo: function(){
			return "firstNameame: " + this.firstName + " " + "LastName: " + this.lastName;
	}
};

console.log(person.getPersonInfo());

person.greet = function(){
	return "Hello, my name is " + this.firstName + " " + this.lastName;
}

console.log(person.greet());


person.email = "john@example.com";
person.age = 18;
console.log(person.firstName + " " + person.lastName);
console.log(person.email);
console.log(person.age);

delete person.isStudent;
console.log(person.isStudent);


let fruits = ["Banana", "Orange", "Apple", "Mango"];

fruits.forEach((fruit, index) => {
	console.log(`Index ${index}: ${fruit}`);
	console.log("----------");
	console.log("Index " + index + ": " + fruit);
});

let text = "<ol>";

/*
for(let i = 0; i < fruits.length; i++){
		text += "<li id='de'>"  + fruits[i] + "</li>"
}
*/

fruits.forEach((fruit) => {
	text += "<li id='de'>"  + fruit + "</li>"
});

text += "</ol>";

document.getElementById("demo2").innerHTML = text;

let cars = ["Toyota", "Honda", "Ford", "BMW"];
let carLength = cars.length;
console.log("Array length: " + carLength);
console.log("Before Sorting:");
console.log(cars);
cars.sort();
console.log("After Sorting:");
console.log(cars);

cars.pop();
console.log("After Pop:");
console.log(cars);

cars.push("Nissan");
console.log("After Push:");
console.log(cars);

cars.shift()
console.log("After Shift:");
console.log(cars);

cars.unshift("Honda")
console.log("After UnShift:");
console.log(cars);
console.log(typeof(cars));
console.log(Array.isArray(cars));


cars.forEach((car) => {
	console.log(car);
});

console.log("==================");

for(let car of cars){
	console.log(car);
}

document.getElementById("demo").innerHTML = cars;


document.getElementById("heading").addEventListener("click", function(){
			
	let elements = document.querySelectorAll("#title1, #title2, #title3");
	
	elements.forEach(element => {
		element.innerHTML = "Updated Heading";
		element.style.color = "blue";
	});
});


