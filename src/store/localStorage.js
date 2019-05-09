export const loadState = () => {
  try {
    const serializedState = localStorage.getItem('bd-iglike');
    if (serializedState === null) {
      return undefined;
    }
    return JSON.parse(serializedState);
  } catch (err) {
    console.log('Erro ao tentar carregar estado a partir do armazenamento local.');
    return undefined;
  }
}

export const saveState = (state) => {
  try {
    const serializedState = JSON.stringify(state);
    localStorage.setItem('bd-iglike', serializedState);
  } catch (err) {
    console.log('Erro ao persistir estado no armazenamento local.');
  }
}
