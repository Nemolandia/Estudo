import React, { useState } from 'react';

function TodoList() {
  const [input, setInput] = useState('');
  const [tasks, setTasks] = useState([]);

  const addTask = () => {
    if (input.trim()) {
      setTasks([...tasks, input]);
      setInput('');
    }
  };

  return (
    <div>
      <h2>To-Do List</h2>
      <input value={input} onChange={(e) => setInput(e.target.value)} />
      <button onClick={addTask}>Adicionar</button>
      <ul>
        {tasks.map((t, i) => <li key={i}>{t}</li>)}
      </ul>
    </div>
  );
}

export default TodoList;
