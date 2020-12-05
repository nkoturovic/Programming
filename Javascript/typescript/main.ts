interface Queryable {
    query() : string;
}

class Student implements Queryable {
    constructor(
        private _indeks : number,
        private _ime : string,
        private _prezime : string
    )  {}

    query(): string {
        return `QUERY ${this._indeks} ${this._ime} ${this._prezime}`;
    }

    get indeks(): number {
        return this._indeks;
    }

    get ime(): string {
        return this._ime;
    }

    get prezime(): string {
        return this._prezime;
    }

    toString(): string {
        return `${this._indeks}, ${this._ime}, ${this._prezime}`;
    }
}

let s = new Student(1392015, "Nebojsa", "Koturovic");
console.log(s); // different from console.log(s.toString());
console.log(s + ""); // same as console.log(s.toString());
console.log(s.ime);
console.log(s.query());
