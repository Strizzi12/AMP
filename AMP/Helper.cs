﻿using System;
using System.Collections.Generic;

namespace AMP {
	public static class Helper {
		public static IEnumerable<T> CatchExceptions<T>(this IEnumerable<T> src, Action<Exception> action = null) {
			using (var enumerator = src.GetEnumerator()) {
				bool next = true;

				while (next) {
					try {
						next = enumerator.MoveNext();
					} catch (Exception ex) {
						action?.Invoke(ex);
						continue;
					}

					if (next) {
						yield return enumerator.Current;
					}
				}
			}
		}

		public static bool IsDigitsOnly(string str) {
			foreach (char c in str) {
				if (c < '0' || c > '9')
					return false;
			}
			return true;
		}

		public static T TransformInput<T>(string input) {
			return (T)Convert.ChangeType(input, typeof(T));
		}
	}
}